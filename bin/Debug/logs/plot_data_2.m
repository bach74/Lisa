figure
load phalangeal_actuator.txt
% time ref y uc angM angV linM linV 
%subplot(3,1,1);
plot(phalangeal_actuator(:,1),phalangeal_actuator(:,2),'r')
hold on
plot(phalangeal_actuator(:,1),phalangeal_actuator(:,4))
xlabel('time')
ylabel('\theta_1')

figure

load metatarsal_actuator.txt
% time ref y uc angM angV linM linV 
%subplot(3,1,2);
plot(metatarsal_actuator(:,1),metatarsal_actuator(:,2),'r')
hold on
plot(metatarsal_actuator(:,1),metatarsal_actuator(:,4))
xlabel('time')
ylabel('\theta_2')

figure

load talus_actuator.txt
% time ref y uc angM angV linM linV 
%subplot(3,1,3);
plot(talus_actuator(:,1),talus_actuator(:,2),'r')
hold on
plot(talus_actuator(:,1),talus_actuator(:,4))
xlabel('time')
ylabel('\theta_3')


