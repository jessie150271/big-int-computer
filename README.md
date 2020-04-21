# BigIntComputer

### Command : 
**Set (Int/Dec/Com) / Print / Assign / Pow / Fac / or any expression.**
>Command和type的第一個字母可為大寫或小寫，第二個字母開始請用小寫

* **Set** *型態(Int/Dec/Com)* *名稱*
* **Set** *型態(Int/Dec/Com)* *名稱* = *運算式*

>設定變數及其型態(與賦值)

* **Print** *名稱*

>印出變數值

* **Assign** *名稱* = *名稱*
* **Assign** *名稱* << *運算式*

>運算式(變數)賦值予變數

* **Pow** *名稱* , *名稱* 
* **Pow** *名稱* ^ *運算式*

>Pow預設型態為Complex,此指令會直接輸出 運算結果 或 錯誤訊息+空值

* **Fac** *名稱*
* **Fac** << *運算式*

>Fac預設型態為Integer,此指令會直接輸出 運算結果 或 錯誤訊息+空值

* 不含空格的任意運算式

>此指令會直接輸出 運算結果 或 錯誤訊息

---
### 運算符號
>本專案使用後序式解析運算式，可輸入 ( ) + - * / ^ ! i -*(負號),並在適當位置加入括號以免錯誤的優先度訊息導致答案有誤
