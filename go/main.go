package main

import (
	"fmt"
	"time"
	"flag" // Very nice
	"os"
)

var debug bool

func transformTimeToHuman(timeInSeconds time.Duration) string {
    hours := timeInSeconds / time.Hour
    timeInSeconds -= hours * time.Hour
    minutes := timeInSeconds / time.Minute
    timeInSeconds -= minutes * time.Minute

    return fmt.Sprintf("%02dh%02dm%02ds", hours, minutes, timeInSeconds / time.Second)
}

func transformHumanToTime(time string) int {
    temp := 0
    minutes := 0
    hours := 0
    seconds := 0
    multi := 1
    
    for _, char := range time {
        if (char == 'h') {
            hours = temp
            temp = 0
            multi = 1
        } else if (char == 'm') {
            minutes = temp
            temp = 0
            multi = 1
        } else if (char == 's') {
            seconds = temp
            // this is only if you add something like 20s10m I could give it support but meh
            break
        } else {
            // This works fine with numbers but you can write 'fas' as 
            // fa seconds wich will be f => 49 and a => 52 and will not be useful
            // I can fix this with a swich statement a little bit more complex
            // but this is ok for now
            temp = temp * multi + int(char - '0')
            multi *= 10
        }
    }

    seconds = hours * 3600 + minutes * 60 + seconds

    if (debug) {
        fmt.Printf("Calculated seconds: %d\n", seconds)
    }

    return seconds
}

func checkParameters() string {
    // This is so beautiful ;)
    flag.BoolVar(&debug, "d", false, "This is only for testing")
    flag.Parse()

    if (debug) {
        return os.Args[2]
    }
    return os.Args[1]
}

func main() {
    humanInput := checkParameters()
    timeInSeconds := time.Duration(transformHumanToTime(humanInput)) * time.Second
    timeInHuman := ""

    fmt.Println("Delete me")
    
    for timeInSeconds > 0 {
        fmt.Printf("\033[1A\033[0G")
        fmt.Printf("\033[K")
        timeInHuman = transformTimeToHuman(timeInSeconds)
        if (timeInSeconds <= 30 * time.Second) {
            fmt.Printf("Timer: \033[31;40m%s\033[0m\n", timeInHuman)
        } else {
            fmt.Printf("Timer: %s\n", timeInHuman)
        }
        timeInSeconds -= 1 * time.Second
        time.Sleep(1 * time.Second)
    }

    fmt.Printf("\033[1A\033[0G")
    fmt.Printf("\033[K")
    fmt.Println("Done!");
}
