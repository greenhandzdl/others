% File_name:三角函数_正弦余弦定义
% Data:2022-1-15
% Author:Greenhandzdl

aplha = 0:pi/40:2*pi; %设置角度为(0,pi)精度pi/40
r = 1; %单位圆半径为1
cir_x = r*cos(aplha); %定义圆横坐标
cir_y = r*sin(aplha); %定义圆纵坐标

x = 0:pi/40:2*pi;
c_x = cir_x*inv(r);
s_y = cir_y*inv(r);

plot(cir_x,cir_y, x,c_x, x,s_y ,'.-') ,legend('单位圆','余弦函数','正弦函数'), xlabel('横坐标代表cosx'),ylabel('纵坐标代表sinx'),title('正弦余弦的初识'),grid on, axis equal;

clear all;