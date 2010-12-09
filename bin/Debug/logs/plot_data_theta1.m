%load phalangeal.txt

nref=1;
nin=3;

time=m(:,1);
% cut first 2 sec
a=find(time>2,1);
b=size(m(:,1));
time=time(a:size(time));

ref=m(a:b,2:1+nref);
y=m(a:b,nref+2:nref+nin);
uc=m(a:b,nref+nin+1);

addit=nref+nin+2;

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
plot(time,ref,'r')
hold on
plot(time,y);
plot(time,uc,'g:');
xlabel('time')
ylabel('\theta_1')

figure
% plot angular momentum
subplot(4,1,1); 
plot(time,angM1(:,1),'r')
hold on
plot(time,angM1(:,2),'g')
plot(time,angM1(:,3),'b')
title('angular momentum');


% plot angular velocity
subplot(4,1,2);
plot(time,angV1(:,1),'r')
hold on
plot(time,angV1(:,2),'g')
plot(time,angV1(:,3),'b')
title('angular velocity');


% plot linear momentum
subplot(4,1,3);
plot(time,linM1(:,1),'r')
hold on
plot(time,linM1(:,2),'g')
plot(time,linM1(:,3),'b')
title('linear momentum');


% plot linear velocity
subplot(4,1,4);
plot(time,linV1(:,1),'r')
hold on
plot(time,linV1(:,2),'g')
plot(time,linV1(:,3),'b')
title('linear velocity');


figure
% plot angular momentum 2
subplot(4,1,1); 
plot(time,angM2(:,1),'r')
hold on
plot(time,angM2(:,2),'g')
plot(time,angM2(:,3),'b')
title('angular momentum');


% plot angular velocity 2
subplot(4,1,2);
plot(time,angV2(:,1),'r')
hold on
plot(time,angV2(:,2),'g')
plot(time,angV2(:,3),'b')
title('angular velocity');


% plot linear momentum 2
subplot(4,1,3);
plot(time,linM2(:,1),'r')
hold on
plot(time,linM2(:,2),'g')
plot(time,linM2(:,3),'b')
title('linear momentum');


% plot linear velocity 2
subplot(4,1,4);
plot(time,linV2(:,1),'r')
hold on
plot(time,linV2(:,2),'g')
plot(time,linV2(:,3),'b')
title('linear velocity');
