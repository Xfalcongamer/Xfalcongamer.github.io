import asyncio
import serial
import websockets

# Change this to your Arduino COM port
SERIAL_PORT = "COM7"  # Change as needed
BAUD_RATE = 9600

# Open serial connection
ser = serial.Serial(SERIAL_PORT, BAUD_RATE)


async def send_joystick_data(websocket, path):
    while True:
        if ser.in_waiting > 0:
            data = ser.readline().decode("utf-8").strip()
            print(f"Sending: {data}")
            await websocket.send(data)


async def main():
    async with websockets.serve(send_joystick_data, "localhost", 8765):
        await asyncio.Future()  # Keeps the server running

asyncio.run(main())  # ✅ This ensures a running event loop