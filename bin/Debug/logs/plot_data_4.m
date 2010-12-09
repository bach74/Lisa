load phalangeal_actuator.txt

t=phalangeal_actuator(:,1);

h=figure;
% time ref y uc angM angV linM linV 
subplot(4,1,1);
plot(t,phalangeal_actuator(:,2),'r')
hold on
plot(t,phalangeal_actuator(:,4))
xlabel('time')
ylabel('\theta_0')

load metatarsal_actuator.txt
% time ref y uc angM angV linM linV 
subplot(4,1,2);
plot(t,metatarsal_actuator(:,2),'r')
hold on
plot(t,metatarsal_actuator(:,4))
xlabel('time')
ylabel('\theta_1')

load talus_actuator.txt
% time ref y uc angM angV linM linV 
subplot(4,1,3);
plot(t,talus_actuator(:,2),'r')
hold on
plot(t,talus_actuator(:,4))
xlabel('time')
ylabel('\theta_2')

load tibia_actuator.txt
% time ref y uc angM angV linM linV 
subplot(4,1,4);
plot(t,tibia_actuator(:,2),'r')
hold on
plot(t,tibia_actuator(:,4))
xlabel('time')
ylabel('\theta_3')

set(h,'Position',[624 21 695 1077]);



