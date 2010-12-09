load phalangeal_l_actuator.txt

t=phalangeal_l_actuator(:,1);
% time ref y uc angM angV linM linV 
plot(t,phalangeal_l_actuator(:,2),'r')
hold on
plot(t,phalangeal_l_actuator(:,4))
xlabel('time')
ylabel('\theta')