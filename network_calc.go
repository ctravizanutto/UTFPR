package main

import (
	"encoding/binary"
	"errors"
	"strconv"
	"strings"
)

type Networks struct {
	networkCount int
	networkSize	[]int
}

func parseData(cData string) (*Networks, error) {
	cDataSlices := strings.Split(cData, " ")
	networkCount, err := strconv.Atoi(strings.ReplaceAll(cDataSlices[0], "\n", ""))
	if err != nil {
		return nil, err
	} else if len(cDataSlices) < networkCount + 1 {
		return nil, errors.New("invalid network size")
	}

	networkSize := make([]int, 0)
	for i := 0; i < networkCount; i++ {
		networkSizeIt, err := strconv.Atoi(strings.ReplaceAll(cDataSlices[i + 1], "\n", ""))
		if err != nil {
			return nil,err
		}
		networkSize = append(networkSize, networkSizeIt)
	}
	
	result := Networks{networkCount: networkCount, networkSize: networkSize}
	return &result, nil
}

func genIPArray(networks* Networks) (string) {
	defaulAddress := binary.BigEndian.Uint32([]byte{192, 168, 0, 0})
	_ = defaulAddress
	for i := 0; i < networks.networkCount; i++ {
		
	}
	return ""
}