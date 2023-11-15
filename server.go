package main

import (
	"bufio"
	"fmt"
	"net"
)

func processData(cData string) (*string, error) {
	networks, err := parseData(cData)
	_ = networks
	if err != nil {
		return nil, err
	}
	// 
	return nil, nil
}

func handleConnection(c net.Conn) {
	fmt.Printf("%s\n", c.RemoteAddr().String())
	cData, err := bufio.NewReader(c).ReadString('\n')
	if err != nil {
		fmt.Println(err)
		return
	}

	result, err := processData(cData)
	if err != nil {
		fmt.Println(err)
		return
	}
	c.Write([]byte(*result))
	c.Close()
}

func main() {
	/*args := os.Args
	if len(args) == 1 {
		fmt.Println("Usage: go run . <PORT_NUMBER>")
		return
	}*/

	//PORT := ":" + args[1]
	PORT:=":8888"
	l, err := net.Listen("tcp", PORT)
	if err != nil {
		fmt.Println(err)
		return
	}
	defer l.Close()

	for {
		c, err := l.Accept()
		if err != nil {
			fmt.Println(err)
			return
		}
		go handleConnection(c)
	}
}
