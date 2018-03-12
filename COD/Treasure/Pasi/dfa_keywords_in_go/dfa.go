package main 

import "fmt"

var tree [500][30] int
var leaf [500] int
var ok [500] bool
var sz int = 1
var keywords []string

func insert(str string) {
	var v int  = 0
	for i := 0; i < len(str); i++ {
		c := str[i] - 'a'
		if ok[tree[v][c]] == false {
			tree[v][c] = sz
			ok[sz] = true
			sz++
		}
		v = tree[v][c]
	}
	leaf[v]++
}

func search(str string) bool {
	var v int  = 0
	for i := 0; i < len(str); i++ {
		c := str[i]-'a'
		if ok[tree[v][c]] == false {
			return false
		}
		v = tree[v][c]
	}
	return leaf[v] > 0
}

func pre() {
	keywords = []string{"auto",    "double", "int",
						"struct",  "break",  "long",
						"switch",  "case",    "enum",
						"char" ,   "extern",  "return",
						"register","typedef", "union",
						"const",    "float",  "short",
						"continue", "for",     "if",
						"else",     "do",      "static", 
						"signed",   "goto",    "default",
						"volatile", "unsigned", "sizeof",
						"void",      "while"}
}

func main() {
	pre()
	for i := 0; i < len(keywords); i++  {
		insert(keywords[i])
	}
	var input string
	fmt.Scanln(&input)
	if search(input) {
		fmt.Println("keyword")
	}else {
		fmt.Println("Not keyword")
	}
}