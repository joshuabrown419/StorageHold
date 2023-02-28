import zmq
import os

"""
--------------------------------------------------------------------------
    Begin code citation:
    Author: Unknown
    Website: ZeroMQ
    Article Title: "Get started"
    URL: https://zeromq.org/get-started/?language=python&library=pyzmq#
    Copyright: The ZeroMQ Authors
    Date: 2022
--------------------------------------------------------------------------
"""

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://127.0.0.1:2046")

print(socket)

while True:
    #  Wait for next request from client
    message = socket.recv()
    print(f"Received request: {message}")

    # Extract filepath from message
    start = message.find(b"|")

    # Initialize message
    error = b""
    reply = b""

    # Check for pipe
    if start < 0:
        error += b"Error: Message must contain '|' to separate int and filepath.\n"
    try:
        id_str = message[0:start].decode("ascii")
        id_int = int(id_str)
    except(ValueError):
        error += b"Error: Message must begin with an integer.\n"

    filepath = message[start+1:].decode("ascii")
    if not filepath:
        error += b"Error: A filepath must be included after '|'.\n"

    # Check that file exists
    if os.path.isfile(filepath):
        if not error:
            with open(filepath, "r") as f:
                file_lines = f.readlines()
                # Read line by line
                count = 1
                for line in file_lines:
                    if error:
                        break
                    index = line.find(",")
                    # Check .csv formatting on each line
                    if index < -1:
                        error += b"Error: Filepath is not a valid .csv format.\n"
                    # Check that first .csv line entry is an integer
                    try:
                        read_id = int(line[0:index])
                        if read_id == id_int:
                            examine = line[start+1:]
                            i = examine.find(",")
                            if i < 1:
                                error += b"Error: on line " + bytes("{count}", "ascii") + b"there is a .csv format violation.\n"
                                break
                            else:
                                str1 = bytes(examine[:i], "ascii")
                                try:
                                    str2 = bytes(examine[i+1:], "ascii")
                                except(IndexError):
                                    str2 = b""
                                # Contruct reply
                                reply += str1 + b"|" + str2
                                break
                    except(ValueError):
                        error += b"Error: .csv lines must begin with integer.\n"
                    count += 1

                
    #  Send reply back to client
    f.close()
    if not error and not reply:
        error += b"Error: ID was not found.\n"
    if error:
        socket.send(error)
    else:
        ending = reply[-1]
        if ending == 10:
            reply = reply[0:-1]
        socket.send(reply)

    """
    --------------------------------------------------------------------------
        End code citation:
        Author: Unknown
        Website: ZeroMQ
        Article Title: "Get started"
        URL: https://zeromq.org/get-started/?language=python&library=pyzmq#
        Copyright: The ZeroMQ Authors
        Date: 2022
    --------------------------------------------------------------------------
    """
