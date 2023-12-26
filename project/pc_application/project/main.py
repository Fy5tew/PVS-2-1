import serial

import config
import handlers


def main():
    try:
        ser = serial.Serial(config.PORT, baudrate=config.BAUDRATE)
    except serial.serialutil.SerialException:
        print(f"Cannot open port '{config.PORT}'");
        return

    if not ser.is_open:
            ser.open()

    print("Serial connection is opened")

    try:
        while True:
            try:
                input_line = ser.readline().decode().strip()
            except UnicodeDecodeError:
                continue

            if input_line:
                command, *values = input_line.split(config.COMMAND_SEPARATOR)
                handler = handlers.get_handler(command)
                result = handler(*values)
                if result:
                    ser.write(f'{result}\r\n'.encode())
                if (config.DEBUG):
                    print(f"!DEBUG:INPUT: {input_line}")
                    print(f"!DEBUG:COMMAND: {command} {values}")
                    print(f"!DEBUG:RESULT: {result}")

    except serial.SerialException as se:
        print(f"Serial error: {se}")

    except KeyboardInterrupt:
        print("Exit by user request")

    finally:
        if ser.is_open:
            ser.close()
            print("Serial connection is closed")


main()
