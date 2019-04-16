#include "jerryscript.h"
#include "cppcodec/base64_rfc4648.hpp"
#include <iostream>
#include <vector>

#define BUFFER_SIZE 256

#ifdef WASM
#include "emscripten.h"
#endif


std::string encode_code(const jerry_char_t*, size_t);

const unsigned char* transferToUC(const uint32_t* arr, size_t length) {
  auto container = std::vector<unsigned char>();
  for (size_t x = 0; x < length; x++) {
    auto _t = arr[x];
    container.push_back(_t >> 24);
    container.push_back(_t >> 16);
    container.push_back(_t >> 8);
    container.push_back(_t);
  }

  return &container[0];
}

std::vector<uint32_t> transferToU32(const uint8_t* arr, size_t length) {
  auto container = std::vector<uint32_t>();
  for (size_t x = 0; x < length; x++) {
    size_t index = x * 4;
    uint32_t y = (arr[index + 0] << 24) | (arr[index + 1] << 16) | (arr[index + 2] << 8) | arr[index + 3];
    container.push_back(y);
  }

  return container;
}

int main (int argc, char** argv) {
  const jerry_char_t script_to_snapshot[] = u8R"(
    [1, 2, 3, 5, 6, 7, 8, 9].map(function(i) {
      return i * 2;
    }).reduce(function(p, i) {
      return p + i;
    }, 0);
  )";
  
  std::cout << encode_code(script_to_snapshot, sizeof(script_to_snapshot)) << std::endl;
  
  return 0;
}

std::string encode_code(const jerry_char_t script_to_snapshot[], size_t length) {
  using base64 = cppcodec::base64_rfc4648;

  // initialize engine;
  jerry_init(JERRY_INIT_SHOW_OPCODES);
  
  jerry_feature_t feature = JERRY_FEATURE_SNAPSHOT_SAVE;

  if (jerry_is_feature_enabled(feature)) {
    static uint32_t global_mode_snapshot_buffer[BUFFER_SIZE];
    
    // generate snapshot;
    jerry_value_t generate_result = jerry_generate_snapshot(
      NULL, 
      0,
      script_to_snapshot,
      length - 1,
      0,
      global_mode_snapshot_buffer,
      sizeof(global_mode_snapshot_buffer) / sizeof(uint32_t));

    if (!(jerry_value_is_abort(generate_result) || jerry_value_is_error(generate_result))) {
      size_t snapshot_size = (size_t) jerry_get_number_value(generate_result);

      std::string encoded_snapshot = base64::encode(
        transferToUC(global_mode_snapshot_buffer, BUFFER_SIZE), BUFFER_SIZE * 4);

      jerry_release_value(generate_result);
      jerry_cleanup();

      // encoded bytecode of the snapshot;
      return encoded_snapshot;
    }
  }
  return "[EOF]";
}

void run_encoded_snapshot(std::string code, size_t snapshot_size) {
  using base64 = cppcodec::base64_rfc4648;
  
  auto result = transferToU32(
    &(base64::decode(code)[0]), 
    BUFFER_SIZE);

  uint32_t snapshot_decoded_buffer[BUFFER_SIZE];
  for (auto x = 0; x < BUFFER_SIZE; x++) {
    snapshot_decoded_buffer[x] = result.at(x);
  }

  jerry_init(JERRY_INIT_EMPTY);

  jerry_value_t res = jerry_exec_snapshot(
    snapshot_decoded_buffer,
    snapshot_size, 0, 0);

  // default as number result;
  std::cout << "[Zero] code running result: " << jerry_get_number_value(res) << std::endl;
  
  jerry_release_value(res);
}

#ifdef WASM
extern "C" {
  void EMSCRIPTEN_KEEPALIVE run_core() {
    // encoded snapshot (will be hardcoded in wasm binary file);
    std::string base64_snapshot = "WVJSSgAAABYAAAAAAAAAgAAAAAEAAAAYAAEACAAJAAEEAgAAAAAABwAAAGcAAABAAAAAWDIAMhwyAjIBMgUyBDIHMgY6CCAIwAIoAB0AAToARscDAAAAAAABAAMBAQAhAgIBAQAAACBFAQCPAAAAAAABAAICAQAhAgICAkUBAIlhbQADAAYAcHVkZXIAAGVjAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA==";
    run_encoded_snapshot(base64_snapshot, 142);
  }
}
#endif
