%% --- Executes on button press in inversebutton.
function inversebutton_Callback(hObject, eventdata, handles)
pos_start=evalin('base','pos_start');
pos_target=evalin('base','pos_target');
jstart=evalin('base','jstart');
j1=jstart(1,1);
j2=jstart(2,1);
j3=jstart(3,1);
a1x =0;
a1y =0;
a1z =0;
if pos_target==pos_start
   errordlg('Set target position first','No Movement'); 
   movement=0;
   assignin('base','movement',movement);
else
   movement=1;
   assignin('base','movement',movement);
   delta=divelo(pos_start,pos_target);
end

while evalin('base','movement')==1
FK=evalin('base','FK');
Jac=Jacobian(FK);
Jacinv=pinv(Jac);
dXYZ=delta(1:3,1)/10;  
dTheta=Jacinv*dXYZ;
dTheta1=radtodeg(dTheta(1,1));
dTheta2=radtodeg(dTheta(2,1));
dTheta3=radtodeg(dTheta(3,1));
j1=j1+dTheta1;
j2=j2+dTheta2;
j3=j3+dTheta3;
a1x = a1x+dTheta1;
a1y = a1y+dTheta2;
a1z = a1z+dTheta3;
FKdraw(j1,j2,j3)
pos_new=[FK(1,16);FK(2,16);FK(3,16)];
delta=divelo(pos_new,pos_target);
EucError=delta(5,1)^2;
OrinError=delta(6,1)^2;
set( handles.textEucE,'String', num2str(EucError,3));

if EucError <10^-2
   movement=0; 
   assignin('base','movement',movement);
   assignin('base','pos_start',pos_new);
   jstart=[j1;j2;j3];
   assignin('base','jstart',jstart);
end 

if all(delta(:) <= 0.1)
   movement=0; 
   assignin('base','movement',movement);
   assignin('base','pos_start',pos_new);
   assignin('base','jstart',jstart);
end 

a1x
a1y
a1z

end
