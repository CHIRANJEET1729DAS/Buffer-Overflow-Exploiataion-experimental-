void lightUpLED() {
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  delay(10000);
  digitalWrite(12, LOW);
}

void checkPassword(char* input) {
  char password[10] = "Chachac";  // The correct password
  char buffer[10];  // Buffer to hold user input (deliberately small)

  // Vulnerable: strcpy doesn't check bounds, potential for buffer overflow
  strcpy(buffer, input);  // Unsafe copy, will cause overflow if input > 9 chars

  // Debugging: Print the contents of buffer and input for verification
  Serial.print("Buffer: ");
  Serial.println(buffer);
  Serial.print("Input: ");
  Serial.println(input);

  // Compare the input with the predefined password
  if (strcmp(buffer, password) == 0) {
    Serial.println("Access Granted");
    lightUpLED();  // Trigger LED on correct password
  } else {
    Serial.println("Access Denied");
  }
}
void setup() {
  Serial.begin(9600);
}

    // Craft the exploit payload (whenever we want to exploit it by buffer overflow )
    // it is just the address of the lED fucntion
    // 8 bytes for buffer overflow, followed by address of lightUpLED (e.g., 0x201)
    //char exploit[50] = "ABCDEFGH";   // 8 bytes for the buffer
    //exploit[8] = '\x01';  // Little-endian byte 1 (LSB)
    //exploit[9] = '\x02'; // Overwrite with the address of lightUpLED (0x201 in HEX)

void loop() {
  // Check if there's data available in the Serial buffer
  if (Serial.available() > 0) {
    char input[50];  // Allocate space for input up to 50 characters (larger than buffer)
    int len = Serial.readBytesUntil('\n', input, sizeof(input) - 1);  // Read until newline
    input[len] = '\0';  // Null-terminate the input string

    // Check the password entered by the user
    checkPassword(input);  // This is where the vulnerability happens
  }
}

