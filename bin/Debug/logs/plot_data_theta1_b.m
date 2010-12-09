%load phalangeal.txt

nref=1;
nin=3;

time=m(:,1);
% cut first 2 sec
a=find(time>2,1);
b=size(m(:,1));
time=time(a:size(time));

ref=m(a:b,2:1+nref);
y=m(a:b,nref+2:nref+nin+1);
uc=m(a:b,nref+nin+2);

addit=nref+nin+3;

angM1=[m(a:b,addit:addit+2)];
angV1=[m(a:b,addit+3:addit+5)];
linM1=[m(a:b,addit+6:addit+8)];
linV1=[m(a:b,addit+9:addit+11)];


angM2=[m(a:b,addit+12:addit+14)];
angV2=[m(a:b,addit+15:addit+17)];
linM2=[m(a:b,addit+18:addit+20)];
linV2=[m(a:b,addit+21:addit+23)];

h=figure
% time ref y uc angM angV linM linV 
subplot(5,1,1);
plot(time,ref);
grid on
xlim([0 10]);
ylabel('\tau_{ref}');
subplot(5,1,2);
plot(time,y(:,2));
grid on
xlim([0 10]);
ylabel('\theta_1');
subplot(5,1,3);
plot(time,y(:,1));
xlim([0 10]);
grid on;
ylabel('\omega_1');
subplot(5,1,4);
plot(time,y(:,3));
grid on
xlim([0 10]);
ylabel('\tau_1');
xlabel('time');
subplot(5,1,5);
plot(time,uc,'b');
xlim([0 10]);
grid on
xlabel('time');
ylabel('U_c');
set(h,'Position',[624 21 695 1077]);
xlim([0 10]);
grid on


print -depsc -tiff -r300 1

% figure
% % plot angular momentum
% plot(time,angM1(:,1),'r')
% hold on
% plot(time,angM1(:,2),'g')
% plot(time,angM1(:,3),'b')
% title('angular momentum');

h=figure
% plot angular momentum 2
subplot(4,1,1);
plot(time,angM2(:,1),'r');
ylabel('Nm');
xlim([0 10]);
grid on
title('angular momentum around x (global frame)');
subplot(4,1,2);
plot(time,angM2(:,2),'g');
xlim([0 10]);
grid on
title('angular momentum around y (global frame)');
ylabel('Nm');
subplot(4,1,3);
plot(time,angM2(:,3),'b');
xlim([0 10]);
grid on
title('angular momentum around z (global frame)');
ylabel('Nm');
subplot(4,1,4);
xlim([0 10]);
grid on
title('angular momentum x (global frame)');
plot(time,y(:,3:3));
ylabel('Nm');
xlabel('time');
set(h,'Position',[624 21 695 1077]);
xlim([0 10]);
grid on
title('angular momentum around motor axis');


print -depsc -tiff -r300 2

% figure
% % plot angular velocity 2
% plot(time,angV2(:,1),'r')
% hold on
% plot(time,angV2(:,2),'g')
% plot(time,angV2(:,3),'b')
% plot(time,y(:,3:3),'bla--');
% title('angular velocity');
