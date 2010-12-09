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

figure
% time ref y uc angM angV linM linV 
plot(time,ref,'c')
hold on
plot(time,y(:,1:2));
%plot(time,uc,'b');
xlabel('time')
ylabel('\theta_1')

% figure
% % plot angular momentum
% plot(time,angM1(:,1),'r')
% hold on
% plot(time,angM1(:,2),'g')
% plot(time,angM1(:,3),'b')
% title('angular momentum');

figure
% plot angular momentum 2
plot(time,angM2(:,1),'r')
hold on
plot(time,angM2(:,2),'g')
plot(time,angM2(:,3),'b')
plot(time,y(:,3:3),'bla--');
title('angular momentum');


% figure
% % plot angular velocity 2
% plot(time,angV2(:,1),'r')
% hold on
% plot(time,angV2(:,2),'g')
% plot(time,angV2(:,3),'b')
% plot(time,y(:,3:3),'bla--');
% title('angular velocity');
