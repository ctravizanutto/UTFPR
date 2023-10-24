package main

import (
	"bufio"
	"encoding/binary"
	"errors"
	"fmt"
	"math/bits"
	"net"
	"strconv"
	"strings"
)

func NextPowOf2(n int) uint32 {
	k := 1
	for ;k < n; {
	   k = k << 1
	}
	return uint32(k)
}

func processData(cData string) (string, error) {
	cDataSlices := strings.Split(cData, " ")
	networkNumber, err := strconv.Atoi(strings.ReplaceAll(cDataSlices[0], "\n", ""))
	if err != nil {
		return "", err
	} else if len(cDataSlices) < networkNumber + 1 {
		return "", errors.New("invalid network size")
	}

	for i := 0; i < networkNumber; i++ {
		mask := binary.BigEndian.Uint32([]byte{0xFF, 0xFF, 0xFF, 0xFF})
		networkSize, err := strconv.Atoi(strings.ReplaceAll(cDataSlices[i], "\n", ""))
		if err != nil {
			return "", err
		}

		resultInt32, carry := bits.Sub32(mask, NextPowOf2(networkSize) - 1, 0)
		resultByte := make([]byte, 4)
		binary.BigEndian.PutUint32(resultByte, resultInt32)

		fmt.Println(resultByte)
		fmt.Println(resultInt32 + carry)
	}
	return "", nil
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
	c.Write([]byte(result))
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
