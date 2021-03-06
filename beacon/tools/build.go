package main

import (
	"fmt"
	"os/exec"
)

func runCmd(workdir string, name string, args ...string) {
	//実行時ディレクトリを指定して flex/bison をコンパイル
	cmd := exec.Command(name, args...)
	cmd.Dir = workdir
	out, err := cmd.Output()
	if err != nil {
		fmt.Println("    fail")
	}
	fmt.Println(string(out))
}

func main() {
	runCmd("src/beacon/parse", "go", "run", "script/gen.go")
	runCmd("src", "make", "rb")
}
