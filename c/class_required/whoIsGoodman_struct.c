   #include <stdio.h>
   typedef enum {
       甲 = 1,
       乙,
       丙,
       丁
   } PEO;

   // 定义一个结构体来表示每个人的陈述
   typedef struct {
       int is_not_self;   // A说不是自己
       int is_c;          // B说的是C
       int is_d;          // C说的是D
       int is_not_d;      // D说C胡说（不是D）
   } Statements;

   // 根据不同的人做好事来生成对应的陈述结构体
   Statements get_statements(PEO who) {
       Statements st;
       switch (who) {
       case 甲:
           st = (Statements){1, 0, 0, 1};
           break;
       case 乙:
           st = (Statements){1, 0, 0, 1};
           break;
       case 丙:
           st = (Statements){1, 1, 0, 1};
           break;
       case 丁:
           st = (Statements){1, 0, 1, 0};
           break;
       default:
           st = (Statements){0, 0, 0, 0};
           break;
       }
       return st;
   }

   int main(void) {
       for (PEO who = 甲; who <= 丁; who++) {
           Statements st = get_statements(who);
           int true_count = st.is_not_self + st.is_c + st.is_d+ st.is_not_d;
           if (true_count == 3) {
               printf("是第%c位同学做的好事\n", who == 甲? '甲' : who == 乙? '乙' : who == 丙? '丙' : '丁');
               break;
           }
       }
       return 0;
   }