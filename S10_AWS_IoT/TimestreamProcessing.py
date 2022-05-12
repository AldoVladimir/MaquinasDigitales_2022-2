#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu May 12 00:26:43 2022

@author: vladimir
"""
# %% Bibliotecas
import boto3
import pandas as pd
import awswrangler as wr 
import numpy as np
from numpy import ma
import matplotlib
# %% Clientes boto3
access = ''
secret = ''

boto3_session = boto3.session.Session(region_name='us-east-1',
                  aws_access_key_id=access,
                  aws_secret_access_key = secret)

timestream_query = boto3.client('timestream-query', 
                                region_name='us-east-1',
                                aws_access_key_id=access,
                                aws_secret_access_key = secret)

# %% Ejecutar consulta
#Tiempo hacia atras en minutos en la consulta
T = 1000 
presion = 10

#Propedeutico de formateo de strings
#En C++
#sprintf(payload,"\"Press_hPa\":%.2f,",presion)
    
#Python
payload = "\"Press_hPa\":{}".format(presion)
payload = f"\"Press_hPa\":{presion}"
payload = f'''
\"Press_hPa\":{presion}
'''
#Código de la consulta SQL
query = f'''
SELECT *
FROM "IoT_MaquinasDigitales"."Atmosfera_Aldo"
WHERE time between ago({T}m) and now()
order by time desc
'''

#Código de la consulta SQL
query = '''
SELECT *
FROM "IoT_MaquinasDigitales"."Atmosfera_Aldo"
WHERE time between ago({}m) and now()
order by time desc
'''.format(T)


#Cliente timestreamquery
timestream_query_result = timestream_query.query(QueryString= query)

#Consulta de la base de datos que se envía a un Data Frame de pandas
query_df =wr.timestream.query(query, 
                              boto3_session = boto3_session)
# %% Transformar measures a columnas
#Pivotear valores big int de luz
light_pivot = query_df[query_df["measure_name"] == 'Luz_adim'].pivot(index = ["time","deviceID"],
                             columns = "measure_name",
                             values = "measure_value::bigint")

#Escribitr presion pivot
pres_pivot = query_df[query_df["measure_name"] == 'Press_hPa'].pivot(index = ["time","deviceID"],
                             columns = "measure_name",
                             values = "measure_value::double")

#Merge de presion y luz


#Eliminar columnas de fecha y ID
light_pivot = light_pivot.reset_index()
light_pivot.drop(columns = "deviceID",inplace = True)
light_pivot.sort_values(by = "time" ,axis=0, ascending=True, inplace=True)

pres_pivot = pres_pivot.reset_index()
pres_pivot.drop(columns = "deviceID",inplace = True)
pres_pivot.sort_values(by = "time" ,axis=0, ascending=True, inplace=True)
# %% Hacer los procesamientos 
light_pivot.plot(x = "time", y = "Luz_adim")
pres_pivot.plot(x = "time", y = "Press_hPa")

# %% Escribir en las bases de datos
'''
col_names = light_pivot.columns.values.tolist()


#Escribir a timestream
rejected_records = wr.timestream.write(
    df=light_pivot,
    database="IoT_Digitalizacion",
    table="Atmosfera_Aldo",
    time_col="time",
    measure_col = col_names,
    dimensions_cols=["deviceID"],
    boto3_session = boto3_session
)

#Escribir a csv
light_pivot.to_csv("./luz_adim.csv")
'''
