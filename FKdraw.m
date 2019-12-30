function [ FK ] = FKdraw( j1,j2,j3 )
%initial parameter
%[j0 j1 j2 j3;d0 d1 d2 d3;a0 a1 a2 a3;t0 t1 t2 t3]
%theta3=360-theta1-theta2
tran1=-1;
tran2=-6.8;
tran3=-7.2;
tran4=[-7.3,-17];
j01=[1,0,0,0;0,1,0,0;0,0,1,tran1;0,0,0,1];
j11p=[cosd(j1) -sind(j1) 0 0; sind(j1) cosd(j1) 0 0; 0 0 1 0; 0 0 0 1;];
j1p2=[1,0,0,0;0,1,0,0;0,0,1,tran2;0,0,0,1];
j22p=[1 0 0 0; 0 cosd(j2) -sind(j2) 0; 0 sind(j2) cosd(j2) 0; 0 0 0 1;];
j2p3=[1,0,0,0;0,1,0,tran3;0,0,1,0;0,0,0,1];
j33p=[1 0 0 0; 0 cosd(j3) -sind(j3) 0; 0 sind(j3) cosd(j3) 0; 0 0 0 1;];
j3pe=[1,0,0,0;0,1,0,tran4(1);0,0,1,tran4(2);0,0,0,1];

p1=j01;
p1r=p1*j11p;
p2=p1r*j1p2;
p2r=p2*j22p;
p3=p2r*j2p3;
p3r=p3*j33p;
pe=p3r*j3pe;

FK1=[p1,p2,p3,pe];
Q=XYZkine(FK1);
%J=Jacobian(FK); 
plot3(Q(1,:),Q(2,:),Q(3,:),'-o','LineWidth',2,'MarkerSize',6,'MarkerFaceColor',[0.5,0.5,0.5]);grid on;%axis([-31,31,-31,31,0,31]);
text(Q(1,5),Q(2,5),Q(3,5),['  (', num2str(Q(1,5),3), ', ', num2str(Q(2,5),3),', ', num2str(Q(3,5),3), ')']);
title('3DOF Pseudo Inverse Jacobian Inverse Kinematic')
xlabel('X Axis');
ylabel('Y Axis');
zlabel('Z Axis');
axis([-30 30 -30 30 -50 30]);
h = rotate3d;
h.Enable = 'on';
h.ActionPostCallback = @mypostcallback;
assignin('base','FK',FK1);
assignin('base','FK1',FK1);
pause(0.1);
end

function mypostcallback(obj,evd)
%disp('A rotation is about to occur.');
ax_properties = get(gca);
assignin('base','pov',ax_properties.View);
end

%use evalin('base',a) to get variable a from workspace 
%assignin('base','a_rms',a_rms) to write variable a_rms to workspace