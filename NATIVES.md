# Types:

### `NATIVE POINTER`

Type containing a raw memory address.

# Enums:

### `ENUM SCRIPT_THREAD_STATE`

Represents the state of a script thread.

```
ENUM SCRIPT_THREAD_STATE
    RUNNING,
    IDLE,
    KILLED,
    PAUSED
ENDENUM
```

# Commands:

### `NATIVE PROC LOG_TO_FILE(VARARGS) = "0x7F41C15A89FDEE9F"`

Writes the provided arguments to a log file located in the script's folder. Each script maintains its own log file, which is automatically truncated when the script is reloaded. Supports variadic arguments of types `INT`, `FLOAT`, `STRING/TEXT_LABEL_*`, and `VECTOR`.

- **Parameters:**
  - `(VARARGS)`: A variable number of arguments to print.
  
**Example Usage:**
```
INT iInt = 1578463
FLOAT fFloat = 789.123
STRING sString = "String"
TEXT_LABEL_63 tlLabel = "("
tlLabel += 121
tlLabel += ")"
VECTOR vVector = <<1215.123, 8792.3, 478.2342>>
LOG_TO_FILE("Hello from script ", GET_THIS_SCRIPT_NAME(), ". Int=", iInt, " Float=", fFloat, " String=", sString, " Label=", tlLabel, " Vector=", vVector)
```

---

## `NATIVE FUNC POINTER MEMORY_SCAN_PATTERN(STRING name, STRING pattern) = "0x0E7D68BA1B32BA2A"`

Scans the game process for an IDA-style pattern and returns the found address.

- **Parameters:**
  - `name (STRING)`: A unique name for your pattern (used for caching).
  - `pattern (STRING)`: The IDA-style pattern to scan for within the game process.

- **Returns:**
  - `POINTER`: The found address, or `NULL` if not found.

**Example Usage:**
```
POINTER pPedFactoryPtr = MEMORY_SCAN_PATTERN("CPedFactory", "48 8B 05 ? ? ? ? 48 8B 40 ? 48 83 C4 20 5E C3 31 C0")
IF pPedFactoryPtr <> NULL
    pPedFactoryPtr = MEMORY_ADD(pPedFactoryPtr, 3)
    pPedFactoryPtr = MEMORY_RIP(pPedFactoryPtr)
    pPedFactoryPtr = MEMORY_DEREF(pPedFactoryPtr) // CPedFactory*
    
    pPedFactoryPtr = MEMORY_ADD(pPedFactoryPtr, 8) // 0x08
    pPedFactoryPtr = MEMORY_DEREF(pPedFactoryPtr) // CPed*
    
    pPedFactoryPtr = MEMORY_ADD(pPedFactoryPtr, 4264) // 0x10A8
    pPedFactoryPtr = MEMORY_DEREF(pPedFactoryPtr) // PlayerInfo*
	
    // Frame Flags
    pPedFactoryPtr = MEMORY_ADD(pPedFactoryPtr, 624) // 0x270

    INT iFlags = MEMORY_READ_INT(pPedFactoryPtr)
    MEMORY_WRITE_INT(pPedFactoryPtr, iFlags | 2048) // 0x800 = explosive ammo
ENDIF
```

---

## `NATIVE FUNC POINTER MEMORY_ADD(POINTER ptr, INT offset) = "0x043339EE866586BD"`

Performs byte-wise pointer arithmetic.

- **Parameters:**
  - `ptr (POINTER)`: Base address.
  - `offset (INT)`: Signed byte offset to add or subtract.

- **Returns:**
  - `POINTER`: Resulting address.

---

## `NATIVE FUNC POINTER MEMORY_RIP(POINTER ptr) = "0x6E496FA081015FC3"`

Resolves a RIP-relative displacement at the given address.

- **Parameters:**
  - `ptr (POINTER)`: Base address.

- **Returns:**
  - `POINTER`: Resolved absolute address.

---

## `NATIVE FUNC POINTER MEMORY_DEREF(POINTER ptr) = "0x9C980189DFBDADAD"`

Dereferences a pointer.

- **Parameters:**
  - `ptr (POINTER)`: Address to dereference.

- **Returns:**
  - `POINTER`: Dereferenced value.

---

## `NATIVE PROC MEMORY_WRITE(POINTER ptr, INT& bytes[]) = "0xD763E0EF3AFCE986"`

Writes raw bytes to memory.

- **Parameters:**
  - `ptr (POINTER)`: Destination address.
  - `bytes (INT[])`: Bytes to write (0–255). The array size determines the number of bytes written.

---

## `NATIVE PROC MEMORY_READ(POINTER ptr, INT& bytes[]) = "0x5353EB6CABD2A870"`

Reads raw bytes from memory.

- **Parameters:**
  - `ptr (POINTER)`: Source address.
  - `bytes (INT[])`: Output buffer. The array size determines the number of bytes read.

---

## `NATIVE PROC MEMORY_WRITE_INT(POINTER ptr, INT value) = "0xA1CDE11FA6D2838F"`

Writes a 32-bit integer to memory.

- **Parameters:**
  - `ptr (POINTER)`: Destination address.
  - `value (INT)`: Value to write.

---

## `NATIVE FUNC INT MEMORY_READ_INT(POINTER ptr) = "0x1884B5B84D20DEF9"`

Reads a 32-bit integer from memory.

- **Parameters:**
  - `ptr (POINTER)`: Address to read from.

- **Returns:**
  - `INT`: Value read from memory.

---

### `NATIVE PROC SET_CURRENT_SCRIPT_THREAD(INT scriptHash) = "0x7AFACDB81809E2C1"`

Spoofs the currently running script thread. Make sure to restore it when you're done with it.

- **Parameters:**
  - `scriptHash (INT)`: The hash of the script to spoof to.

**Example Usage:**
```
INT oldHash = GET_HASH_OF_THIS_SCRIPT_NAME()
SET_CURRENT_SCRIPT_THREAD(HASH("shop_controller"))
// Do your stuff.
SET_CURRENT_SCRIPT_THREAD(oldHash)
```

---

### `NATIVE PROC SET_SCRIPT_THREAD_STATE(INT scriptHash, SCRIPT_THREAD_STATE state) = "0x2B53D1F2FAD6DB0E"`

Modifies the state of a running script thraed.

- **Parameters:**
  - `scriptHash (INT)`: The hash of the script.
  - `state (SCRIPT_THREAD_STATE)`: The state to set to.

**Example Usage:**
```
SET_SCRIPT_THREAD_STATE(HASH("fm_street_dealer"), PAUSED)
```

---

### `NATIVE PROC SCRIPT_STATIC_SET_INT(INT scriptHash, INT index, INT value) = "0x857A2700DC9407CF"`

Writes the given integer value to the script static at the given index.

- **Parameters:**
  - `scriptHash (INT)`: The hash of the script.
  - `index (INT)`: The index of the static.
  - `value (INT)`: The value to write.

**Example Usage:**
```
SCRIPT_STATIC_SET_INT(HASH("freemode"), 19447 + 176, 0)
```

---

### `NATIVE PROC SCRIPT_STATIC_SET_FLOAT(INT scriptHash, INT index, FLOAT value) = "0xD8AABF55B8C2ABCC"`

Writes the given float value to the script static at the given index.

- **Parameters:**
  - `scriptHash (INT)`: The hash of the script.
  - `index (INT)`: The index of the static.
  - `value (FLOAT)`: The value to write.

**Example Usage:**
```
SCRIPT_STATIC_SET_FLOAT(HASH("freemode"), 444, -12.50)
```

---

### `NATIVE PROC SCRIPT_STATIC_SET_STRING(INT scriptHash, INT index, STRING value) = "0xBBED7EBD9CB32457"`

Writes the given string value to the script static at the given index.

- **Parameters:**
  - `scriptHash (INT)`: The hash of the script.
  - `index (INT)`: The index of the static.
  - `value (STRING)`: The value to write.

**Example Usage:**
```
SCRIPT_STATIC_SET_STRING(HASH("freemode"), 3985, "Hello World!")
```

---

### `NATIVE PROC SCRIPT_STATIC_SET_TEXT_LABEL(INT scriptHash, INT index, STRING value, INT size) = "0x82486D97F828522B"`

Writes the given text label value to the script static at the given index.

- **Parameters:**
  - `scriptHash (INT)`: The hash of the script.
  - `index (INT)`: The index of the static.
  - `value (STRING)`: The value to write.
  - `size (INT)`: The size of the text label (8, 16, 24, 32, or 64).

**Example Usage:**
```
SCRIPT_STATIC_SET_TEXT_LABEL(HASH("freemode"), 4995, "Hello World!", 24)
```

---

### `NATIVE PROC SCRIPT_STATIC_SET_VECTOR(INT scriptHash, INT index, VECTOR value) = "0x1CBDE8A15884D019"`

Writes the given vector value to the script static at the given index.

- **Parameters:**
  - `scriptHash (INT)`: The hash of the script.
  - `index (INT)`: The index of the static.
  - `value (VECTOR)`: The value to write.

**Example Usage:**
```
SCRIPT_STATIC_SET_VECTOR(HASH("freemode"), 16363, <<247.1122, -1817.5349, 26.1894>>)
```

---

### `NATIVE FUNC INT SCRIPT_STATIC_GET_INT(INT scriptHash, INT index) = "0xE60444296FBC9C3C"`

Reads the integer value from the script static at the given index.

- **Parameters:**
  - `scriptHash (INT)`: The hash of the script.
  - `index (INT)`: The index of the static.

- **Returns:**
  - `INT`: The integer value stored at the static.

**Example Usage:**
```
INT value = SCRIPT_STATIC_GET_INT(HASH("freemode"), 19447 + 176)
```

---

### `NATIVE FUNC FLOAT SCRIPT_STATIC_GET_FLOAT(INT scriptHash, INT index) = "0x02917A468A9F9203"`

Reads the float value from the script static at the given index.

- **Parameters:**
  - `scriptHash (INT)`: The hash of the script.
  - `index (INT)`: The index of the static.

- **Returns:**
  - `FLOAT`: The float value stored at the static.

**Example Usage:**
```
FLOAT value = SCRIPT_STATIC_GET_FLOAT(HASH("freemode"), 444)
```

---

### `NATIVE FUNC STRING SCRIPT_STATIC_GET_STRING(INT scriptHash, INT index) = "0x50AECCD9E4A23B3A"`

Reads the string value from the script static at the given index.

- **Parameters:**
  - `scriptHash (INT)`: The hash of the script.
  - `index (INT)`: The index of the static.

- **Returns:**
  - `STRING`: The string value stored at the static.

**Example Usage:**
```
STRING value = SCRIPT_STATIC_GET_STRING(HASH("freemode"), 3985)
```

---

### `NATIVE FUNC STRING SCRIPT_STATIC_GET_TEXT_LABEL(INT scriptHash, INT index) = "0x83C64F9F51CCB284"`

Reads the text label value from the script static at the given index.

- **Parameters:**
  - `scriptHash (INT)`: The hash of the script.
  - `index (INT)`: The index of the static.

- **Returns:**
  - `STRING`: The text label value stored at the static.

**Example Usage:**
```
STRING value = SCRIPT_STATIC_GET_TEXT_LABEL(HASH("freemode"), 4995)
```

---

### `NATIVE FUNC VECTOR SCRIPT_STATIC_GET_VECTOR(INT scriptHash, INT index) = "0x022347480BDA5340"`

Reads the vector value from the script static at the given index.

- **Parameters:**
  - `scriptHash (INT)`: The hash of the script.
  - `index (INT)`: The index of the static.

- **Returns:**
  - `VECTOR`: The vector value stored at the static.

**Example Usage:**
```
VECTOR value = SCRIPT_STATIC_GET_VECTOR(HASH("freemode"), 16363)
```

---

### `NATIVE FUNC POINTER SCRIPT_STATIC_GET_POINTER(INT scriptHash, INT index) = "0x8B1A5E688A9ABF31"`

Reads the pointer value from the script static at the given index.

- **Parameters:**
  - `index (INT)`: The index of the global.

- **Returns:**
  - `POINTER`: The address of the static.

**Example Usage:**
```
POINTER value = SCRIPT_STATIC_GET_POINTER(HASH("freemode"), 16019)
```

---

### `NATIVE PROC SCRIPT_GLOBAL_SET_INT(INT index, INT value) = "0xE308F800129466D7"`

Writes the given integer value to the script global at the given index.

- **Parameters:**
  - `index (INT)`: The index of the global.
  - `value (INT)`: The value to write.

**Example Usage:**
```
SCRIPT_GLOBAL_SET_INT(1882048 + 1 + (1 + (0 * 15)), 0)
```

---

### `NATIVE PROC SCRIPT_GLOBAL_SET_FLOAT(INT index, FLOAT value) = "0xCE23B2BC1A4037EE"`

Writes the given float value to the script global at the given index.

- **Parameters:**
  - `index (INT)`: The index of the global.
  - `value (FLOAT)`: The value to write.

**Example Usage:**
```
SCRIPT_GLOBAL_SET_FLOAT(1882048 + 1 + (1 + (0 * 15)) + 13, 9999.0)
```

---

### `NATIVE PROC SCRIPT_GLOBAL_SET_TEXT_LABEL(INT index, STRING value, INT size) = "0xC7540C6E3F588A63"`

Writes the given text label value to the script global at the given index.

- **Parameters:**
  - `index (INT)`: The index of the global.
  - `value (STRING)`: The value to write.
  - `size (INT)`: The size of the text label (8, 16, 24, 32, or 64).

**Example Usage:**
```
SCRIPT_GLOBAL_SET_TEXT_LABEL(2359296 + (1 + (0 * 5571)) + 681 + 2463 + (1 + (0 * 8)), "Hello World!", 32)
```

---

### `NATIVE PROC SCRIPT_GLOBAL_SET_VECTOR(INT index, VECTOR value) = "0x2D670A4779E7390E"`

Writes the given vector value to the script global at the given index.

- **Parameters:**
  - `index (INT)`: The index of the global.
  - `value (VECTOR)`: The value to write.

**Example Usage:**
```
SCRIPT_GLOBAL_SET_VECTOR(1882048 + 1 + (1 + (0 * 15)) + 10, <<247.1122, -1817.5349, 26.1894>>)
```

---

### `NATIVE FUNC INT SCRIPT_GLOBAL_GET_INT(INT index) = "0x95257993CA3F052E"`

Reads the integer value from the script global at the given index.

- **Parameters:**
  - `index (INT)`: The index of the global.

- **Returns:**
  - `INT`: The integer value stored at the global.

**Example Usage:**
```
INT value = SCRIPT_GLOBAL_GET_INT(1882048 + 1 + (1 + (0 * 15)))
```

---

### `NATIVE FUNC FLOAT SCRIPT_GLOBAL_GET_FLOAT(INT index) = "0xDC21946AD79CBEAF"`

Reads the float value from the script global at the given index.

- **Parameters:**
  - `index (INT)`: The index of the global.

- **Returns:**
  - `FLOAT`: The float value stored at the global.

**Example Usage:**
```
FLOAT value = SCRIPT_GLOBAL_GET_FLOAT(1882048 + 1 + (1 + (0 * 15)) + 13)
```

---

### `NATIVE FUNC STRING SCRIPT_GLOBAL_GET_TEXT_LABEL(INT index) = "0x79516115C6DB77F2"`

Reads the text label value from the script global at the given index.

- **Parameters:**
  - `index (INT)`: The index of the global.

- **Returns:**
  - `STRING`: The text label value stored at the global.

**Example Usage:**
```
STRING value = SCRIPT_GLOBAL_GET_TEXT_LABEL(2359296 + (1 + (0 * 5571)) + 681 + 2463 + (1 + (0 * 8)))
```

---

### `NATIVE FUNC VECTOR SCRIPT_GLOBAL_GET_VECTOR(INT index) = "0x673E810DC3EC1307"`

Reads the vector value from the script global at the given index.

- **Parameters:**
  - `index (INT)`: The index of the global.

- **Returns:**
  - `VECTOR`: The vector value stored at the global.

**Example Usage:**
```
VECTOR value = SCRIPT_GLOBAL_GET_VECTOR(1882048 + 1 + (1 + (0 * 15)) + 10)
```

---

### `NATIVE FUNC POINTER SCRIPT_GLOBAL_GET_POINTER(INT index) = "0x3424D8FD1E8EDBE1"`

Reads the pointer value from the script global at the given index.

- **Parameters:**
  - `index (INT)`: The index of the global.

- **Returns:**
  - `POINTER`: The address of the global.

**Example Usage:**
```
POINTER value = SCRIPT_GLOBAL_GET_POINTER(1968933)
```

---

### `NATIVE PROC SCRIPT_FUNCTION_BEGIN_CALL(INT scriptHash, INT pc) = "0xC0E22B4A435AC866"`

Begins building a script function call. You must provide the hash of the script and the program counter (PC) where the function is located. This can be followed by one or more `SCRIPT_FUNCTION_ADD_PARAM_*` calls if the target function supports, and then must be finalized with one of the `SCRIPT_FUNCTION_END_CALL_*` variants.

- **Parameters:**
  - `scriptHash (INT)`: The hash of the script containing the function.
  - `pc (INT)`: The address of the function within the script.

**Example Usage:**
```
VEHICLE_INDEX veh = GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), TRUE)
POINTER ptr1 = SCRIPT_STATIC_GET_POINTER(HASH("AM_MP_VEHICLE_REWARD"), 176)
POINTER ptr2 = SCRIPT_STATIC_GET_POINTER(HASH("AM_MP_VEHICLE_REWARD"), 129 + 4)
POINTER ptr3 = SCRIPT_STATIC_GET_POINTER(HASH("AM_MP_VEHICLE_REWARD"), 129 + 5)
POINTER ptr4 = SCRIPT_STATIC_GET_POINTER(HASH("AM_MP_VEHICLE_REWARD"), 129 + 6)
POINTER ptr5 = SCRIPT_STATIC_GET_POINTER(HASH("AM_MP_VEHICLE_REWARD"), 129 + 7)
SCRIPT_FUNCTION_BEGIN_CALL(HASH("AM_MP_VEHICLE_REWARD"), 8527)
SCRIPT_FUNCTION_ADD_PARAM_INT(NATIVE_TO_INT(veh))
SCRIPT_FUNCTION_ADD_PARAM_POINTER(ptr1)
SCRIPT_FUNCTION_ADD_PARAM_POINTER(ptr2)
SCRIPT_FUNCTION_ADD_PARAM_POINTER(ptr3)
SCRIPT_FUNCTION_ADD_PARAM_POINTER(ptr4)
SCRIPT_FUNCTION_ADD_PARAM_POINTER(ptr5)
SCRIPT_FUNCTION_ADD_PARAM_INT(0)
SCRIPT_FUNCTION_ADD_PARAM_INT(1)
SCRIPT_FUNCTION_ADD_PARAM_INT(1)
SCRIPT_FUNCTION_ADD_PARAM_INT(0)
SCRIPT_FUNCTION_ADD_PARAM_INT(0)
SCRIPT_FUNCTION_ADD_PARAM_INT(-1)
INT retn = SCRIPT_FUNCTION_END_CALL_INT()
```

---

### `NATIVE PROC SCRIPT_FUNCTION_ADD_PARAM_INT(INT value) = "0x08498C0E9D0B40FF"`

Adds an integer parameter to the current function call.

- **Parameters:**
  - `value (INT)`: The integer value to push.

---
  
### `NATIVE PROC SCRIPT_FUNCTION_ADD_PARAM_FLOAT(FLOAT value) = "0x77447CC2B714B3CD"`

Adds a float parameter to the current function call.

- **Parameters:**
  - `value (FLOAT)`: The float value to push.

---

### `NATIVE PROC SCRIPT_FUNCTION_ADD_PARAM_STRING(STRING value) = "0x274DF0AFD6AE55ED"`

Adds a string parameter to the current function call.

- **Parameters:**
  - `value (STRING)`: The string value to push.

---

### `NATIVE PROC SCRIPT_FUNCTION_ADD_PARAM_VECTOR(VECTOR value) = "0x4C033060974B7B16"`

Adds a vector parameter to the current function call.

- **Parameters:**
  - `value (VECTOR)`: The vector value to push.

---

### `NATIVE PROC SCRIPT_FUNCTION_ADD_PARAM_POINTER(POINTER value) = "0x6D56C40AE63AF5EB"`

Adds a pointer parameter to the current function call.

- **Parameters:**
  - `value (POINTER)`: The pointer value to push.

---

### `NATIVE PROC SCRIPT_FUNCTION_ADD_PARAM_REFERENCE_INT(INT& value) = "0x23C957EA2CAC32C1"`

Adds an integer reference to the current function call.

- **Parameters:**
  - `value (INT&)`: Reference to the integer variable.

---

### `NATIVE PROC SCRIPT_FUNCTION_ADD_PARAM_REFERENCE_FLOAT(FLOAT& value) = "0xD1F101417313D51C"`

Adds a float reference to the current function call.

- **Parameters:**
  - `value (FLOAT&)`: Reference to the float variable.

---

### `NATIVE PROC SCRIPT_FUNCTION_ADD_PARAM_REFERENCE_TEXT_LABEL_15(TEXT_LABEL_15& value) = "0x5C322B4B4444B1D5"`

Adds a 15-character text label reference to the current function call.

- **Parameters:**
  - `value (TEXT_LABEL_15&)`: Reference to the text label variable.

---

### `NATIVE PROC SCRIPT_FUNCTION_ADD_PARAM_REFERENCE_TEXT_LABEL_23(TEXT_LABEL_23& value) = "0xE4FED9824D4F4506"`

Adds a 23-character text label reference to the current function call.

- **Parameters:**
  - `value (TEXT_LABEL_23&)`: Reference to the text label variable.

---

### `NATIVE PROC SCRIPT_FUNCTION_ADD_PARAM_REFERENCE_TEXT_LABEL_31(TEXT_LABEL_31& value) = "0x3A991D3A46ED3946"`

Adds a 31-character text label reference to the current function call.

- **Parameters:**
  - `value (TEXT_LABEL_31&)`: Reference to the text label variable.

---

### `NATIVE PROC SCRIPT_FUNCTION_ADD_PARAM_REFERENCE_TEXT_LABEL_63(TEXT_LABEL_63& value) = "0xB8051D0558A34D66"`

Adds a 63-character text label reference to the current function call.

- **Parameters:**
  - `value (TEXT_LABEL_63&)`: Reference to the text label variable.

---

### `NATIVE PROC SCRIPT_FUNCTION_ADD_PARAM_REFERENCE_VECTOR(VECTOR& value) = "0x51A946C23ABD71E8"`

Adds a vector reference to the current function call.

- **Parameters:**
  - `value (VECTOR&)`: Reference to the vector variable.

---

### `NATIVE PROC SCRIPT_FUNCTION_ADD_PARAM_REFERENCE_STRUCT(STRUCT& value) = "0xBB8A36B6AF274653"`

Adds a struct reference to the current function call.

- **Parameters:**
  - `value (STRUCT&)`: Reference to the struct variable.

---

### `NATIVE PROC SCRIPT_FUNCTION_END_CALL_PROC() = "0x56A2FF1109E4288A"`

Ends the current function call and executes it. Use this when the function does not return a value.

---

### `NATIVE FUNC INT SCRIPT_FUNCTION_END_CALL_INT() = "0x21448D2E73E6268B"`

Ends the current function call and executes it, returning an integer.

- **Returns:**
  - `INT`: The return value of the called function.

---

### `NATIVE FUNC FLOAT SCRIPT_FUNCTION_END_CALL_FLOAT() = "0xD67665C45FB0350D"`

Ends the current function call and executes it, returning a float.

- **Returns:**
  - `FLOAT`: The return value of the called function.

---

### `NATIVE FUNC STRING SCRIPT_FUNCTION_END_CALL_STRING() = "0xCF772F62E284AC66"`

Ends the current function call and executes it, returning a string.

- **Returns:**
  - `STRING`: The return value of the called function.

---

### `NATIVE FUNC VECTOR SCRIPT_FUNCTION_END_CALL_VECTOR() = "0xBDAC87D43E99E594"`

Ends the current function call and executes it, returning a vector.

- **Returns:**
  - `VECTOR`: The return value of the called function.