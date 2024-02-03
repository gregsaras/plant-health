package main

import (
	"fmt"
	"net"
	"os"
)

func main() {
	listener, err := net.Listen("tcp", "0.0.0.0:8080")
	if err != nil {
		fmt.Println("Error:", err)
		return
	}
	defer listener.Close()

	fmt.Println("Server is listening on port 8080")

	for {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Println("Error:", err)
			continue
		}

		go handleClient(conn)
	}
}

func handleClient(conn net.Conn) {
	defer conn.Close()

	buffer := make([]byte, 1024)

	for {
		n, err := conn.Read(buffer)
		if err != nil {
			fmt.Println("Error:", err)
			return
		}

		go writeMessage(string(buffer[:n]))
	}
}

func writeMessage(str string) {
	if _, err := os.Stat("../data.csv"); err != nil {
		if os.IsNotExist(err) {
			f, err := os.Create("../data.csv")
			if err != nil {
				fmt.Println("Failed to create")
				return
			}
			f.Close()
		}
	}

	f, err := os.OpenFile("../data.csv", os.O_APPEND|os.O_WRONLY, 0644)
	defer f.Close()

	if err != nil {
		fmt.Println(err)
		return
	}

	line, err := fmt.Fprintln(f, str)
	if err != nil {
		fmt.Println(err)
		return
	}

	fmt.Println(line, "bytes written")
}
