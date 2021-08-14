package main

import (
	"bufio"
	"fmt"
	"io/ioutil"
	"os"
	"path"
	"regexp"
	"strconv"
	"strings"
	"time"
)

func main() {
	showTips()
	execute()
	time.Sleep(10 * time.Second) /** 如果不是自己点击退出，5秒自动退出 */
}

func showTips() {
	tips := []string{
		"请输入文件夹路径:",
		"文件夹的图片被批量改名;",
		"例如：",
		"C:/headImages/ 1 6 46",
		"指headImages文件夹，第1-5张图是封面，6-45是目录，46及后是正文",
		"请输入："}
	itemLen := len(tips)
	for i := 0; i < itemLen; i++ {
		if i == itemLen-1 {
			fmt.Printf(tips[i])
		} else {
			fmt.Println(tips[i])
		}
	}
}
type InputArgs struct {
	LocalPath  string /** 输入的目录或文件路径 */
	fengm    int    /** 封面 */
	topic      int    /** 目录 */
	zhengw   int /** 正文 */
}
var inputArgs InputArgs
func execute() {
	reader := bufio.NewReader(os.Stdin)
	data, _, _ := reader.ReadLine()
	reg := regexp.MustCompile("\\s+")
	inputstr:= reg.ReplaceAllString(string(data), " ")
	strPice := strings.Split(inputstr, " ") /** 空格 */
	if len(strPice) < 4 {
		fmt.Printf("输入有误，参数数量不足,请重新输入或退出程序：")
		execute()
		return
	}

	inputArgs.LocalPath = strPice[0]
	inputArgs.fengm, _ = strconv.Atoi(strPice[1])
	inputArgs.topic, _ = strconv.Atoi(strPice[2])
	inputArgs.zhengw, _ = strconv.Atoi(strPice[3])

	pathTemp, _, _ := isPictureFormat(inputArgs.LocalPath)
	if pathTemp == "" {
		fmt.Println("开始批量改名...")
		inputArgs.LocalPath=strings.ReplaceAll(inputArgs.LocalPath,"\\","/")
		rs := []rune(inputArgs.LocalPath)
		end := len(rs)
		substr := string(rs[end-1 : end])
		if substr != "/" {
			inputArgs.LocalPath = inputArgs.LocalPath + "/"
		}
		getFilelist(inputArgs)
	}

}

/** 是否是图片 */
func isPictureFormat(path string) (string, string, string) {
	temp := strings.Split(path, ".")
	if len(temp) <= 1 {
		return "", "", ""
	}
	mapRule := make(map[string]int64)
	mapRule["jpg"] = 1
	mapRule["png"] = 1
	mapRule["jpeg"] = 1
	// fmt.Println(temp[1]+"---")
	/** 添加其他格式 */
	if mapRule[temp[1]] == 1 {
		println(temp[1])
		return path, temp[1], temp[0]
	} else {
		return "", "", ""
	}
}

func getFilelist(arg InputArgs) {
	//fs.ReadDir()
	//entries, err :=  filepath.Walk(arg.LocalPath,f WalkFunc())
	entries, err := ioutil.ReadDir(arg.LocalPath)
	if err !=nil{
		fmt.Println(err.Error())
		return
	}
	var s string
	var j int
	for i,entry :=range entries{

		if entry.IsDir() {continue}
		if i>=arg.zhengw-1 {
		   if s=="3正文" {
		   	 j++
		   }else{
		   	  j=1
		   	  s="3正文"
		   }
		}else if i>=arg.topic-1{
			if s=="2目录"{
				j++
			}else{j=1;s="2目录"}
		}else{
			if s=="1封面"{
				j++
			}else{j=1;s="1封面"}
		}
		fmt.Println(entry.Name())
		os.Rename( arg.LocalPath+entry.Name(),fmt.Sprintf("%s%s%03d%s",arg.LocalPath,s,j,path.Ext(entry.Name())))
	}

	//oldfilename:= filepath.Base(localPath)

}