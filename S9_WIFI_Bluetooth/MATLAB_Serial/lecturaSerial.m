%% Setup del puerto serie
%Búsqueda de todos los puertos serie
serialportlist
bluetoothlist

%% Conexion
%Asignar un objeto serial y su tasa de baudios
if (ispc)
    %s=serialport("COM4",115200)
    s = bluetooth("Axolote_ESP32")
else
    s=serialport("/dev/ttyUSB0",115200)
end
configureTerminator(s,"CR/LF")
%% Setup de la captura
%Nombre de la variable
name="analogRead";
figure('Name',name,'NumberTitle','off');

%Crea objeto de línea animada
%Añadir conforme se necesiten más
h=animatedline;

%Coloca líneas paralelas al plot
ax=gca;
ax.YGrid='on';

%Tiempo durante el cual se va a medir
measureTime=seconds(60);
t=seconds(0);

%Longitud de la lectura
numReads = 5; %Cantidad de lecturas antes de dibujar. Recomendado: Valor grande para taza de muestreo alta
numCols = 2; %Numero de variables capturadas
data = zeros(numReads,numCols); %Matriz de datos temporales
n=0:numReads-1; %Vector de número de muestra
%% Lectura y ploteo
%Libera el buffer de Matlab para puerto serial
flush(s);
%Leerá una linea completa y nos dejará al inicio
%De una nueva línea.
readline(s);

%Obtiene la fecha del sistema y la guarda
startTime=datetime('now');

while t<=measureTime  %Grabado con tiempo fijo
    
   %Leerá mútiples lecturas antes de dibujar.
   %Dibujar es lento
   for i=1:numReads
       data(i,:) = str2num(readline(s));
   end
   n=n+numReads;    
  
   %Proceso para dibujar
   addpoints(h,n,data(:,1)); %Añade los puntos a la linea animada
   
   %Ajusta los limites de x
   ax.XLim=[n(end)-1000 n(end)];
   
   %Actualiza toda la información a la linea animada
   drawnow

   %Momento final de la muestra
   endTime=datetime('now');
   
   %Tiempo transcurrido
   t=endTime-startTime;   
   title("Elapsed Time: "+seconds(t)+"s");
end