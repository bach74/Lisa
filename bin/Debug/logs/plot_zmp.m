zmp=load('zmp_tibia.txt');

%pos(x,y,z) angM(x,y,z) linM(x,y,z) linV(x,y,z) acc(x,y,z) mass


%interpoliraj radi sporijeg cometa
ii=10;

%zamijeni z i y, tj.
%rotiraj za razliku koordinatnih sustava rot=(90,[1 0 0]);
rot=[1 0 0;0 0 -1;0 1 0];

% zanemari prvih xx tocaka
a=70;
b=length(zmp);

pos0=(rot*[interp(zmp(a:b,1),ii) interp(zmp(a:b,2),ii) interp(zmp(a:b,3),ii)]')';
angM0=(rot*[interp(zmp(a:b,4),ii) interp(zmp(a:b,5),ii) interp(zmp(a:b,6),ii)]')';
linM0=(rot*[interp(zmp(a:b,7),ii) interp(zmp(a:b,8),ii) interp(zmp(a:b,9),ii)]')';
linV0=(rot*[interp(zmp(a:b,10),ii) interp(zmp(a:b,11),ii) interp(zmp(a:b,12),ii)]')';
acc0=(rot*[interp(zmp(a:b,13),ii) interp(zmp(a:b,14),ii) interp(zmp(a:b,15),ii)]')';
mass0=interp(zmp(a:b,16),ii);

% get min and max val

minx=min(min(pos0));
maxx=max(max(pos0));

figure(1)
plot3(pos0(:,1),pos0(:,2),pos0(:,3));
axis([minx maxx minx maxx 0 maxx]);
xlabel('x');
ylabel('y');
zlabel('z');
grid on
hold on
ax=(rot*[0 0 0;1 0 0;0 0 0;0 1 0;0 0 0;0 0 1]')';
line(ax(1:2,1),ax(1:2,2),ax(1:2,3),'Color','r','LineWidth',2);
line(ax(3:4,1),ax(3:4,2),ax(3:4,3),'Color','g','LineWidth',2);
line(ax(5:6,1),ax(5:6,2),ax(5:6,3),'Color','b','LineWidth',2);

shg;
set(get(gcf,'CurrentAxes'),'CameraPosition',[15.2705  -16.5481   14.4904]);
set(get(gcf,'CurrentAxes'),'CameraViewAngle',10.3791);
set(get(gcf,'CurrentAxes'),'CameraViewAngleMode','auto');

comet3(pos0(:,1),pos0(:,2),pos0(:,3));