%close all
clear all
l=load('debug.log');
%t=l(2:length(l),1)-l(2,1);
t=l(2:length(l),1);
%zmp_x=l(2:length(l),2);
%zmp_y=l(2:length(l),3);
%zmp_z=l(2:length(l),4);
error_x=l(2:length(l),2);
error_y=l(2:length(l),3);
error_z=l(2:length(l),4);
gcog_x=l(2:length(l),5);
gcog_y=l(2:length(l),6);
gcog_z=l(2:length(l),7);

tt=l(2:length(l),9);
m_x=l(2:length(l),10);
m_y=l(2:length(l),11);
m_z=l(2:length(l),12);


figure
stairs(t,error_z)
xlabel('time [s]')
ylabel('error z-pos')
grid on
hold on
shg