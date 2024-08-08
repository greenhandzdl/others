% File_name:三角函数_正弦余弦定义
% Data:2022-1-15
% Author:Greenhandzdl

aplha = 0:pi/40:2*pi; %设置角度为(0,2pi)精度pi/40
r = 1; %单位圆半径为1
cir_x = r*cos(aplha); %定义圆横坐标
cir_y = r*sin(aplha); %定义圆纵坐标

x = 0:pi/40:2*pi; %一个普普通通的x轴
c_x = cir_x*inv(r); %接受cos的函数
s_y = cir_y*inv(r); %接受sin的函数
tfction = c_x\s_y; %c_x左除s_y定义tan函数


plot(cir_x,cir_y, x,c_x, x,s_y, x,tfction ,'.-') ,legend('单位圆','余弦函数','正弦函数','正切函数'), xlabel('x轴'),ylabel('y轴'),title('正弦余弦的初识','对于单位圆来说,横坐标代表cos(x)纵坐标代表sin(x)，其中用x与y的比定义正切函数'),grid on, axis equal;

ax = gca; %
ax.XAxisLocation = 'origin'; %建立x轴
ax.YAxisLocation = 'origin'; %建立y轴
ax.FontSize = 15; %设置标题字体
box off; %

clear all;

%Feature(?):在单位圆上能出现一条可移动的横线来分别显示各个函数的值