clear();
Connect_Arduino();
b= [3,1,4,1,5,9,2,6,5,3,5,8,9,7];
%{
writeDigitalPin(a,'d2',1);
pause(1);
writeDigitalPin(a,'d2',0);
writeDigitalPin(a,'d3',1);
pause(1);
writeDigitalPin(a,'d3',0);
writeDigitalPin(a,'d4',1);
pause(1);
writeDigitalPin(a,'d4',0);
writeDigitalPin(a,'d5',1);
pause(1);
writeDigitalPin(a,'d5',0);
writeDigitalPin(a,'d6',1);
pause(1);
writeDigitalPin(a,'d6',0);
writeDigitalPin(a,'d7',1);
pause(1);
writeDigitalPin(a,'d7',0);
writeDigitalPin(a,'d8',1);
pause(1);
writeDigitalPin(a,'d8',0);
writeDigitalPin(a,'d9',1);
pause(1);
writeDigitalPin(a,'d9',0);
writeDigitalPin(a,'d10',1);
pause(1);
writeDigitalPin(a,'d10',0);
writeDigitalPin(a,'d11',1);
pause(1);
writeDigitalPin(a,'d11',0);
%}
for x= 1: 14
    if(b(x) == 0)
      writeDigitalPin(a,'d2',1);
pause(1);
writeDigitalPin(a,'d2',0);
    elseif(b(x) == 1)
      writeDigitalPin(a,'d3',1);
pause(1);
writeDigitalPin(a,'d3',0);
    elseif(b(x) == 2)
      writeDigitalPin(a,'d4',1);
pause(1);
writeDigitalPin(a,'d4',0);
    elseif(b(x) == 3)
      writeDigitalPin(a,'d5',1);
pause(1);
writeDigitalPin(a,'d5',0);
        elseif(b(x) == 4)
      writeDigitalPin(a,'d6',1);
pause(1);
writeDigitalPin(a,'d6',0);
        elseif(b(x) == 5)
      writeDigitalPin(a,'d7',1);
pause(1);
writeDigitalPin(a,'d7',0);
        elseif(b(x) == 6)
      writeDigitalPin(a,'d8',1);
pause(1);
writeDigitalPin(a,'d8',0);
        elseif(b(x) == 7)
      writeDigitalPin(a,'d9',1);
pause(1);
writeDigitalPin(a,'d9',0);
        elseif(b(x) == 8)
      writeDigitalPin(a,'d10',1);
pause(1);
writeDigitalPin(a,'d10',0);
        elseif(b(x) == 9)
      writeDigitalPin(a,'d11',1);
       pause(1);writeDigitalPin(a,'d11',0);
     end
end
    
