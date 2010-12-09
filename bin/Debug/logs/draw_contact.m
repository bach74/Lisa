c=load('contact.log');
% pos [x y z] force (pressure) [x y z]


cind=c(:,1);
ctime=c(:,2);
cx=c(:,3);
% exchange y and z
cy=c(:,5);
cz=c(:,4);
cfx=c(:,6);
cfy=c(:,8);
cfz=c(:,7);


% first find out how many points are (maximum) number of contact points in
% one report

maxPoints=0;
maxX=-inf;
maxY=-inf;
maxZ=-inf;
maxXF=-inf;
maxYF=-inf;
maxZF=-inf;
minX=+inf;
minY=+inf;
minZ=+inf;

i=1;
while (i<length(c))
    index=c(i,1);
    j=i;
    indexnext=index;
    numPoints=0;
    while ((indexnext==index)&&(j<length(c)))
        %p(index,j)=c(j,2:4);
        j=j+1;
        numPoints=numPoints+1;
        indexnext=cind(j);
        maxPoints=max(numPoints,maxPoints);
        maxX=max(cx(j),maxX);
        maxY=max(cy(j),maxY);
        maxZ=max(cz(j),maxZ);
        maxXF=max(cfx(j),maxXF);
        maxYF=max(cfy(j),maxYF);
        maxZF=max(cfz(j),maxZF);
        minX=min(cx(j),minX);
        minY=min(cy(j),minY);
        minZ=min(cz(j),minZ);
    end
    i=i+numPoints;
end

% draw the contact points
i=1;
n=length(c);
h=figure;
xlabel('x');
ylabel('y');
zlabel('z');
axis([minX-abs(minX)*0.2 maxX+abs(maxXF) minY-abs(minY)*0.2 maxY+abs(maxYF) minZ-abs(minZ)*0.2 maxZ+abs(maxZF)]);
grid on
hold on;
set(h,'Renderer','OpenGL')
shg;
ll1=plot(0,0);
ll2=plot(0,0);
ll3=plot(0,0);
while (i<n)
    delete(ll3);
    delete(ll2);
    delete(ll1);
    index=c(i,1);
    j=i;
    indexnext=index;
    numPoints=1;
    clear x y z xf yf zf
    while ((j<=n)&&(cind(j)==index))
        x(numPoints)=cx(j);
        y(numPoints)=cy(j);
        z(numPoints)=cz(j);
        xf(numPoints)=cfx(j);
        yf(numPoints)=cfy(j);
        zf(numPoints)=cfz(j);

        if abs(xf(numPoints))<1e-5 xf(numPoints)=1e-5; end
        if abs(yf(numPoints))<1e-5 yf(numPoints)=1e-5; end
        if abs(zf(numPoints))<1e-5 zf(numPoints)=1e-5; end
        
        numPoints=numPoints+1;
        j=j+1;
    end
%     for k=numPoints:maxPoints
%         x(k)=0;
%         y(k)=0;
%         z(k)=0;
%         xf(k)=0;
%         yf(k)=0;
%         zf(k)=0;
%     end
    
    cop=[sum(x.*xf)/sum(xf) sum(y.*yf)/sum(yf) sum(z.*zf)/sum(zf)];
    
    %rezultantna sila 
    copF=[sum(x.*xf)/sum(x) sum(y.*yf)/sum(y) sum(z.*zf)/sum(z)];
    
    title(ctime(i));
    ll1=quiver3(x,y,z,xf,yf,zf,0,'LineWidth',10);
    ll2=plot3(x,y,z,'x','LineWidth',10);
    ll3=plot3(cop(1),cop(2),cop(3),'or','LineWidth',15);
    pause(0.002);
%[i ctime(i)]
%[ x' y' z' xf' yf' zf']
%pause
    i=i+numPoints-1;
end
