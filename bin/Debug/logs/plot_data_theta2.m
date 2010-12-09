load metatarsal.txt

time=metatarsal(:,1);
% cut first 2 sec
a=find(time>2,1);
b=size(metatarsal(:,1));
time=time(a:size(time));

ref=metatarsal(a:b,2);
y=metatarsal(a:b,3);
uc=metatarsal(a:b,4);

angM1=[metatarsal(a:b,5) metatarsal(a:b,6) metatarsal(a:b,7)];
angV1=[metatarsal(a:b,8) metatarsal(a:b,9) metatarsal(a:b,10)];
linM1=[metatarsal(a:b,11) metatarsal(a:b,12) metatarsal(a:b,13)];
linV1=[metatarsal(a:b,14) metatarsal(a:b,15) metatarsal(a:b,16)];


angM2=[metatarsal(a:b,17) metatarsal(a:b,18) metatarsal(a:b,19)];
angV2=[metatarsal(a:b,20) metatarsal(a:b,21) metatarsal(a:b,22)];
linM2=[metatarsal(a:b,23) metatarsal(a:b,24) metatarsal(a:b,25)];
linV2=[metatarsal(a:b,26) metatarsal(a:b,27) metatarsal(a:b,28)];

figure
% time ref y uc angM angV linM linV 
plot(time,ref,'r')
hold on
plot(time,y);
plot(time,uc,'g:');
xlabel('time')
ylabel('\theta_2')

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


% figure
% % plot angular momentum 2
% subplot(4,1,1); 
% plot(time,angM2(:,1),'r')
% hold on
% plot(time,angM2(:,2),'g')
% plot(time,angM2(:,3),'b')
% title('angular momentum');
% 
% 
% % plot angular velocity 2
% subplot(4,1,2);
% plot(time,angV2(:,1),'r')
% hold on
% plot(time,angV2(:,2),'g')
% plot(time,angV2(:,3),'b')
% title('angular velocity');
% 
% 
% % plot linear momentum 2
% subplot(4,1,3);
% plot(time,linM2(:,1),'r')
% hold on
% plot(time,linM2(:,2),'g')
% plot(time,linM2(:,3),'b')
% title('linear momentum');
% 
% 
% % plot linear velocity 2
% subplot(4,1,4);
% plot(time,linV2(:,1),'r')
% hold on
% plot(time,linV2(:,2),'g')
% plot(time,linV2(:,3),'b')
% title('linear velocity');
