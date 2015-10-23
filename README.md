# EZLoggerV1

請貼下面兩行在你的gecko code  

\#define GECKO  

\#include "ezlogger.h"  

複製ezlogger.h到你目錄下  

使用上只需寫P(_(你的變數),...)即可全部印出不須判別型別,超無腦der  

也可以換顏色  

PR -> LIGHT_RED  

PG -> LIGHT_GREEN  

PB -> LIGHT_BLUE  

也可以傳入指定顏色  

PX0(EZ_RED);  

PX0(EZ_LIGHT_RED);  

PX0(EZ_GREEN);  

PX0(EZ_LIGHT_GREEN);  

PX0(EZ_BLUE);  

PX0(EZ_LIGHT_BLUE);  

PX0(EZ_DARY_GRAY);  

PX0(EZ_CYAN);  

PX0(EZ_LIGHT_CYAN);  

PX0(EZ_PURPLE);  

PX0(EZ_LIGHT_PURPLE);  

PX0(EZ_BROWN);  

PX0(EZ_YELLOW);  

PX0(EZ_LIGHT_GRAY);  

PR0();  

PG0();  

PB0();  

依序印出來的顏色是  

<a href="" target="_blank"><img src="https://dl.dropboxusercontent.com/u/15611020/color.png"/></a>  

P加上0意思是不帶入參數的(Workaround for g++ portability)  

加上

main.cpp經過測試會印出  

<a href="" target="_blank"><img src="https://dl.dropboxusercontent.com/u/15611020/result.png"/></a>  

##NS_WARNING_COLOR  

如果#define NS_WARNING_COLOR, 行為是會把NS_WARNING變紅色  

##MOZ_LOG_886  
如果#define MOZ_LOG_886, 行為是會把PR_LOG導到printf_stderr然後套上藍色  

#know issue
我不知道怎麼盼別是不是在gecko下 所以用\#ifdef GECKO

#特別修正
- 把function都加上static, 變成static linkage 多個cpp include他也不要重複定義.
- 加上一個TAG 方便grep吧? 可以動態改TAG = "你要的字串".
- 把一些菜市場命名都冠上EZ_ prefix怕衝名.