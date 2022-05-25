Archivos Indexados

Ejercicio 2.3.1.a
Dado un fichero secuencial de Facturas, ordenado por Nro. de Cliente y Nro. de Factura, con la siguiente estructura:

FACTURAS Ordenado por Nro_Cliente, Nro_Factura
Nro_ClienteNro_FacturaFechaImporte

Se desea un listado con el siguiente detalle:

Nro. Cliente	Nombre Cliente	Numero Factura

Los datos del cliente se encuentran en un fichero indexado por Nro. de Cliente, que tiene la siguiente estructura:

CLIENTES Indexado por Nro_Cliente

Nro_ClienteNombreDNICUITDomicilio

Accion 2.3.1.a ES

	Ambiente

		tFACTURAS = reg 

			Nro_Cliente
			Nro_Factura
			Fecha
			Importe

		fr

		tCLIENTES = reg

			Nro_Cliente
			Nombre
			DNI
			CUIT
			Domicilio

		fr

		arFAC:archivo de tFACTURAS Ordenado por Nro_Cliente, Nro_Factura
		arCLI:archivo de tCLIENTES Indexado por Nro_Cliente

		rFAC:tFACTURAS
		rCLI:tCLIENTES

	Proceso

		AbrirE/(arFAC)
		AbrirE/s(arCLI)
		Leer(arFAC,r)

		Esc("Desea utilizar el programa V/F")
		leer(op)

		Si op = 'V' Entonces
			Esc('Nro.Cliente/NombreCliente/NroFactura')
		Fsi

		Mientras op <> 'F' Hacer

			rCLI.Nro_Factura:=''

			Mientras NFDA(arFAC) Hacer

				rCLI.Nro_Cliente:=rFAC.Nro_Cliente
				Leer(arCLI,rCLI)

					Si existe Entonces

						Esc(rCLI.Nro_Cliente,'/',rCLI.Nombre,'/',rFAC.Nro_Factura)

					Sino

						Esc('El cliente nro : ',rCLI.Nro_Cliente,' NO EXISTE.')

					Fsi

				Leer(arFAC,r)
			Fm

			Esc("Desea utilizar nuevamente el programa V/F")
			leer(op)

		Fm

		Cerrar(arFAC)
		Cerrar(arCLI)

FA

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Ejercicio 2.3.1.b
Dado un fichero secuencial de Facturas, ordenado por Nro. de Cliente y Nro. de Factura, con la siguiente estructura:

FACTURAS Ordenado por Nro_Cliente, Nro_Factura
Nro_ClienteNro_FacturaFechaImporte

Los datos del cliente se encuentran en un fichero indexado por Nro. de Cliente, que tiene la siguiente estructura:

CLIENTES Indexado por Nro_Cliente

Nro_ClienteNombreDNICUITDomicilio

Se desea un listado con el siguiente detalle:
Nro. Cliente	Nombre Cliente	Total Facturado	Cantidad de Facturas


Accion 2.3.1.b ES 

	Ambiente

		tFACTURAS = reg 

			Nro_Cliente
			Nro_Factura
			Fecha
			Importe

		fr

		tCLIENTES = reg

			Nro_Cliente
			Nombre
			DNI
			CUIT
			Domicilio

		fr

		arFAC:archivo de tFACTURAS Ordenado por Nro_Cliente, Nro_Factura
		arCLI:archivo de tCLIENTES Indexado por Nro_Cliente

		rFAC:tFACTURAS
		rCLI:tCLIENTES
		
		res_Nro_Cliente,ct,tf:entero

	Proceso

		AbrirE/(arFAC)
		AbrirE/s(arCLI)
		Leer(arFAC,r)

		ct:=0
		tf:=0

		Esc("Desea utilizar el programa V/F")
		leer(op)

		Mientras op <> 'F' Hacer

			Esc('Nro_Cliente	NombreCliente	TotalFacturado	Cantidad_de_Facturas')
			rCLI.Nro_Factura:=''

			Mientras NFDA(arFAC) Hacer

				rCLI.Nro_Cliente:=rFAC.Nro_Cliente
				Leer(arCLI,rCLI)

					Si existe Entonces

						res_Nro_Cliente:=rFAC.Nro_Cliente

						Mientras NFDA(arFAC) y (res_Nro_Cliente = rFAC.Nro_Cliente) Entonces

							ct:=ct+1
							tf:=tf+rFAC.Importe
							leer(arFAC,rFAC)

						Fsi

						Esc(rCLI.Nro_Cliente,'/',rCLI.Nombre,'/',tf,'/',ct)

						tf:=0
						ct:=0

					Sino

						Esc('El cliente nro : ',rCLI.Nro_Cliente,' NO EXISTE.')
						Leer(arFAC,r)

					Fsi
				
			Fm

			Esc("Desea utilizar nuevamente el programa V/F")
			leer(op)

		Fm

		Cerrar(arFAC)
		Cerrar(arCLI)

FA

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Ejercicio 2.3.2
Una empresa dispone de un fichero secuencial con datos de sus empleados, ordenado por número de sucursal,
 y categoría, con los siguientes datos:

EMPLEADOS Ordenado por Nro_Sucursal, Categoria
Nro_SucursalCategoria (A,B,C)Nombre_EmpleadoCod_CursoTecnico (si,no)

Y un fichero con datos de cursos, indexado por código de curso:

CURSO Indexado por Cod_Curso
Cod_CursoNombreFechaCant_Horas

Emitir un listado informando:

Para cada empleado: sucursal, categoría, nombre del empleado y nombre del curso que debe realizar.
Por sucursal, categoría y toda la empresa:
Total empleados técnicos
Total empleados no técnicos
Total empleados

Accion 2.3.2 ES 

	Ambiente 

		tfecha = reg

			dd
			mm 
			yy

		fr

		tEMPLEADOS = reg

			Cod_Curso
			Nro_Sucursal
			Categoria:AN(1)//('A','B','C')
			Nombre_Empleado
			Tecnico:AN(2)//('si','no')

		fr

		tCURSO = reg

			Cod_Curso
			Nombre
			Fecha:tfecha
			Cant_Horas

		fr

		arEMP:archivo de tEMPLEADOS Ordenado por Nro_Sucursal, Categoria
		arCUR:archivo de tCURSO Indexado por Cod_Curso

		rEMP:tEMPLEADOS
		rCUR:tCURSO
		op:logico

		c_tec,c_Ntec,c_st,c_Nst,c_tec_total,c_Ntec_total:entero
		res_nro_sucursal:entero
		res_categoria:AN(1)

		Subaccion corte_sucursal ES

			corte_categoria

			Esc('Sucursal:',res_nro_sucursal)
			Esc('Cantidad de tecnicos de la sucursal',c_st)
			Esc('Cantidad de empleados no formados de la sucursal:',c_Nst)

			c_tec_total:=c_tec_total+c_st
			c_Ntec_total:=c_tec_total+c_Nst

			c_st:=0;c_Nst:=0;

			res_nro_sucursal:=rEMP.Nro_Sucursal

		Fs 

		Subaccion corte_categoria ES 

			//i'm here
			Esc('Categoria:',res_categoria)
			Esc('Cantidad de tecnicos de la categoria:',c_tec)
			Esc('Cantidad de empleados no formados de la categoria:',c_Ntec)

			ct_st:=ct_st+c_tec
			ct_Nst:=ct_Nst+c_Ntec

			c_tec:=0
			c_Ntec:=0

			res_categoria:=rEMP.categoria

		Fs

	Proceso

		AbrirE/S(arCUR)
		AbrirE/(arEMP)
		Leer(arEMP,rEMP)

		c_tec:=0;c_Ntec:=0
		c_st:=0;c_Nst:=0;
		c_tec_total:=0
		c_Ntec_total:=0

		res_nro_sucursal:=rEMP.Nro_Sucursal
		res_categoria:=rEMP.Categoria

		Esc('sucursal/categoría/nombre del empleado/nombre del curso')

			Mientras NFDA(arEMP) Hacer

					// trato el index
					rCUR.Cod_Curso:=rEMP.Cod_Curso
					Leer(arCUR,rCUR)

					Si EXISTE Entonces
							Esc(rEMP.Nro_Sucursal,'/',rEMP.Categoria,'/',rEMP.Nombre_Empleado,'/',rCUR.Nombre)
					Sino 
							Esc('El curso no existe.')
					Fsi

					// trato el corte
					Si 	res_nro_sucursal <> rEMP.Nro_Sucursal Entonces
						corte_sucursal
					Sino
						Si res_categoria = rEMP.categoría Entonces
							corte_categoria
						Fsi	
					Fsi
					Si rEMP.Tecnico = 'si' Entonces
							c_tec:=c_tec+1
					Sino
							c_Ntec:=c_Ntec+1
					Fsi

					Leer(arEMP,rEMP)	

			FM	

				corte_sucursal

				Esc('TOTAL TEC',c_tec_total)
				ESC('TOTAL NO TEC:',c_Ntec_total)
				ESC('TOTAL EMPLEADOS:' ,c_tec_total+c_Ntec_total)

		Cerrar(arCUR)
		Cerrar(arEMP)

FA

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Ejercicio 2.3.3
Los automovilistas pasan por el peaje del Puente Gral. Belgrano y deben pagar según su categoría,
 pero además, 

Teniendo en cuenta el archivo siguiente, construya el algoritmo que realice lo que corresponda:
 genere el comprobante, 
 indicando el importe a pagar o emita un mensaje indicando que ya pasó anteriormente.
  si ya han pasado previamente dentro del día tienen pase libre.
 Además indique cuales deberían ser los datos de entrada.
// se debe pedir categoria, patente y fecha

PEAJE Indexado por Patente, Fecha

Patente XXX-NNNFecha N(8)Ult_Hora N(4)Costo XXX,XX



Costo por categoria

Categoria	Costo
1	1,20
2	2,50
3	4,00
4	5,00

Accion 2.2.3 ES

	Ambiente

		tfecha = reg

			dd 
			mm 
			yy

		fr

		tPEAJE = reg 

			Patente:AN(7)
			Fecha:tfecha
			Ult_Hora:N(4)
			Costo:N(3,2)

		fr

		arPEA:archivo de tPEAJE Indexado por Patente, Fecha
		r:tPEAJE
		op,pase:logico
		rescategoria,resfecha,res

	Proceso

		AbrirE/S(arPEA)

		pase:=F

		Esc("Desea utilizar el programa v/f")
		leer(op)

		Mientras op <> 'f' Hacer// se debe pedir categoria, patente y fecha

			Esc('Ingrese la patente':)
			leer(r.Patente)

			Leer(arPEA,r)

			Si existe Entonces

				Esc('Ingrese la fecha')
				leer(resfecha)
				Esc('Ingrese la categoria')
				leer(rescat)

				Si resfecha <> r.fecha Entonces

					r.fecha:=resfecha

					Segun r.categoria Hacer
						1:
							r.Costo:=1.2
						2:
							r.Costo:=2,5
						3:
							r.Costo:=4
						4:
							r.Costo:=5
					Fs

				Sino
					pase:=V
				Fsi

				Esc('Ingrese la hora:')
				leer(r.Ult_Hora)

				Esc('Patente:', r.patente)
				Esc('Fecha:',r.fecha)
				Esc('Categoria:', r.categoria)
				Esc('Ultima hora:', r.Ult_Hora)
				Si pase = 'V' Entonces
					Esc('Costo: 0')
					r.costo:=0
				Sino
					Esc('Costo:',r.Costo)
				Fsi

				RE-ESCRIBIR(arPEA,r)

				pase:=F

			Sino
				Esc("La patente del auto no existe.")
			Fsi

			Esc("Desea utilizar nuevamente el programa v/f")
			leer(op)

		fm

		Cerrar(arPEA)

FA

//CODIGO EN:24M 
//DESK TEST llevo:15M, el 62% del tiempo me llevaria hacer una DESK TEST de este codigo

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// PD: ME PARECE QUE ESTA MAL EL CODIGO

Ejercicio 2.3.4
Crear un algoritmo que simule el trabajo de una caja de supermercado.

 El algoritmo debe permitir imprimir el ticket de compra y 
 realizar el descuento de stock del producto. 

 Al generar el comprobante del ticket debe guardar los datos en
  los archivos TICKET y DETALLE_TICKET

  (el cliente es: "consumidor final" y el NroTicket se genera automáticamente,
   mediante la función OBTENER_TICKET).

Archivos:

PRODUCTOS Indexado por Cod_Prod
Cod_ProdNombreStockPrecio

TICKET Indexado por Nro_Ticket
Nro_TicketFechaCliente

DETALLE_TICKET Indexado por Nro_Ticket
Nro_TicketNro_LineaCod_ProdCantidad

Comprobante:

Empresa:	......................................	CUIT:	.... - ............ - ...	Fecha:	... / ... / ...
Cliente	.................................................................................................................................
Producto	Cantidad	Subtotal
..............................	..............................	..............................
..............................	..............................	..............................
..............................	..............................	..............................
Total	..............................

Accion 2.3.4 ES

	Ambiente

		tfecha = reg 

			dd
			mm 	
			yy

		fr

		tPRODUCTOS = reg

			Cod_Prod
			Nombre
			Stock
			Precio

		fr

		tTICKET = reg 

			Nro_Ticket
			Fecha:tfecha
			Cliente

		fr

		tDETALLE_TICKET = reg 

			Nro_Ticket
			Nro_Linea
			Cod_Prod
			Cantidad

		fr

		tAUX = reg 

			nombreprod:
			cantidad:
			subtotal:

		fr

		arDET:archivo de tDETALLE_TICKET Indexado por Nro_Ticket
		arTIC:archivo de tTICKET Indexado por Nro_Ticket
		arPRO:archivo de tPRODUCTOS Indexado por Cod_Prod
		arAUX:archivo de tAUX

		rDET:tDETALLE_TICKET
		rTIC:tTICKET
		rPRO:tPRODUCTOS
		rAUX:tAUX

		resempresa:AN
		rescuit:entero
		subtotal:entero
		total:=real

	Proceso

		AbrirE/S(arDET);
		AbrirE/S(arTIC);
		AbrirE/S(arPRO);
		AbrirS/(arAUX,rAUX)

		Esc("Desea utilizar el programa: V/F")
		leer(op)

		total:=0

		Mientras op <> 'f' Hacer

			Esc('Ingrese el nombre de la empresa')
			leer(resempresa)

			Esc('Ingrese el CUIT')
			leer(rescuit)

			Esc('Ingrese el codigo del producto')
			Leer(rPRO.Cod_Prod)

			Leer(arPRO,rPRO)

			Si Existe Entonces

				Si rPRO.stock > 0 Entonces

					rTIC.fecha:=fechaACTUAL()

					Esc("ingrese el nro de linea")
					leer(rDET.Nro_Linea)

					Esc('Ingrese la cantidad')
					leer(rDET.Cantidad)

					Si rDET.cantidad > rPRO.stock Entonces // SI LO QUE PIDO ES MAYOR A LO QUE HAY
						
						repetir
							rDET.Cantidad:=NILL // ENTONCES CANTIDAD PEDIDA NULA
							Esc('ERROR, La cantidad ingresada es mayor que la del stock disponible')
							Esc('Ingrese la cantidad')
							leer(rDET.Cantidad) // SE QUEDA ATRAPADO HASTA QUE LA CANT SEA = o menor a la de stock
						hasta que (rDET.cantidad <= rPRO.stock)

					Fsi					

					// DESCUENTO AL STOCK DE PRODUCTOS
					rPRO.stock:=rPRO.stock-rDET.cantidad
					
					// PASAR DATOS AL TICKET
					rTIC.Cliente:='consumidor final'
					rTIC.Nro_Ticket:=OBTENER_TICKET

					// PASAR DATOS AL DETALLE
					rDET.Nro_Ticket:=OBTENER_TICKET
					rDET.Cod_Prod:=rPRO.Cod_Prod

					// GUARDO en el auxiliar: Nombre del producto, Cantidad, Subtotal
					rAUX.nombreprod:=rPRO.nombre
					rAUX.cantidad:=rDET.cantidad
					rAUX.subtotal:=rPRO.precio*rDET.cantidad 

					Escribir(arAUX,rAUX)	// PASO EL PRODUCTO AL AUXILIAR P/ IMPRIMIR LUEGO
					ESCRIBIR(arDET,rDET)	// SE CREA NEW reg DETALLE
					ESCRIBIR(arTIC,rTIC)	// SE CREA NEW reg TICKET
					RE-ESCRIBIR(arPRO,rPRO) // RE ESCRIBO X EL STOCK CAMBIA DEL REG
				
				Sino

					Esc('ERROR, NO HAY STOCK DEL PROD')

				Fsi

			Sino

				Esc('ERROR EL PROD NO EXISTE')

			Fsi


			Esc("Desea agregar otro producto?: V/F")
			leer(op)

		Fm

		Cerrar(arDET);Cerrar(arTIC);Cerrar(arPRO);Cerrar(arAUX)

		AbrirE/(arAUX,rAUX) // IMPRIMO TODO EN EL ORDEN SOLICITADO

		Esc('Empresa: ',resempresa ,' CUIT: ', rescuit,' Fecha: ', fechaACTUAL())
		Esc('Cliente: CONSUMIDOR FINAL')
		Esc('Producto:			Cantidad:			 Subtotal:')

		Mientras NFDA(arAUX) Hacer

			
			Esc(rAUX.nombreprod,'		',rAUX.Cantidad,'		',rAUX.subtotal)
			total:=total+subtotal
			Leer(arAUX,rAUX)

		Fm

		Esc('						Total:',total)


		Cerrar(arAUX)

FA

//CODIGO: 54m
//DESK TEST: 33m

// PD: ME PARECE QUE ESTA MAL EL CODIGO

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Ejercicio 2.3.5
Para poder comprar dólares en una entidad bancaria al precio oficial ($9,40), 
el beneficiario, debe tener un ingreso promedio en los últimos 12 meses equivalente 
a dos veces el sueldo mínimo vital y móvil (el cual en la actualidad es de $5000 por mes). 
Luego, con el sueldo del mes actual, 
solo se permite comprar por un importe no superior al 30% del mismo.
Por ej.: si una persona tiene un sueldo de $10.000, desde septiembre del año pasado,
 al dia de hoy esa persona cumple la condición para comprar y
  puede comprar dólares por un monto máximo de $3.000 (equivalente a U$S 319).
Para ello se cuenta con dos archivos indexados:

CABECERA_SUELDO Indexado por DNI, Periodo, Nro_Recibo

DNI N(8)Periodo N(6)Nro_Recibo N(15)ApyNom AN(50)Empresa AN(50)
El periodo está representado por 6 caracteres numéricos dispuestos de forma de año/mes (aaaamm).
 El número de recibo (Nro_Recibo) es único. Una persona puede tener varios recibos de sueldo.
  La clave de este archivo es DNI, Periodo y Nro_Recibo.

RECIBO Indexado por Nro_Recibo

Nro_Recibo N(15)Concepto N(8)Tipo (0..2)Monto N(15,2)
El campo tipo puede contener los siguientes valores:
 0 - Sueldo básico, 1 – Otros Ingresos, 2 – Descuentos. 
 Para calcular el sueldo mínimo se suman el sueldo (tipo 0),
  y los otros ingresos (tipo 1), NO se restan los descuentos. La clave es Nro_Recibo.

Dado el escenario descripto, se pide escribir dos algoritmos:

Que el empleado del Banco ingrese un número de documento de algún interesado en comprar dólares, 
y le devuelva si está habilitado o no para comprar y, en caso positivo, 
cuál es el monto máximo en pesos que se le autoriza.
Si el interesado desea comprar, solicite el monto en pesos que destinará a la compra,
el cual deberá ser descontado de su cuenta.
 Los datos de la cuenta están en un archivo indexado con la siguiente estructura (indexado por DNI):

DNI N(8)Nro_Cuenta N(25)Saldo N(15,2)
Los puntos a) y b) se repiten hasta que el operador (empleado del Banco) indique que desea finalizar.

Procesar peticiones de compra, de acuerdo a un archivo de entrada de peticiones, 
evaluando si es posible realizar la operación o no. Si no es posible,
 indicar cual es el motivo: 1 – No tiene el ingreso promedio suficiente, o 2 – Pide más del 30 % de su sueldo actual.

PETICIONES

DNI N(8)Cant_Soli N(15,2)
El resultado de la evaluación se debe grabar en un nuevo archivo de salida con el siguiente formato:

SALIDA

DNI N(8)Cant_Soli N(15,2)Pudo (si,no)Error 1..2

FALTA HACER 

Accion 2.3.5 ES

	Ambiente

		tclave = reg 
			DNI N(8)
			Periodo N(6)
			Nro_Recibo N(15)
		fr

		tCABECERA_SUELDO = reg 

			clave: tclave
			ApyNom AN(50)
			Empresa AN(50)

		fr

		tRECIBO = reg 

			Nro_Recibo N(15)
			Concepto N(8)
			Tipo (0..2)
			Monto N(15,2)

		fr

		tPERSONA = reg 

			DNI N(8)
			Nro_Cuenta N(25)
			Saldo N(15,2)

		fr

		//consigna 2
		tPETICIONES = reg

			DNI N(8)
			Cant_Soli N(15,2)

		fr

		tSAL = reg 

			DNI N(8)
			Cant_Soli N(15,2)
			Pudo (si,no)
			Error 1..2

		fr

		
		arPER:archivo de tPERSONA Indexado por DNI
		arREC:archivo de tRECIBO Indexado por Nro_Recibo
		arCAB:archivo de tCABECERA_SUELDO Indexado por clave

		arPET:archivo de tPETICIONES ordenado por DNI
		arSAL:archivo de tSALIDA 

		rCAB:tCABECERA_SUELDO // CONSIGNA 1
		rREB:tRECIBO
		rPER:tPERSONA

		rPET:tPETICIONES // CONSIGNA 2
		arSAL:tSAL

		op:logico
		opn:N(1)
		resperiodo,monto:entero
		maxARS,DNIg,sueldo:entero
		autorizacion:logico
		maxUSD:entero

		Procedimiento Menu() ES
			Esc('Elija una opcion:')
			Esc('1_ TEST DE ESTADO')
			Esc('2_ COMPRAR $')
			Esc('3_Procesar peticiones de compra:')
			Esc('4_ Salir')
		Fp

		Funcion opcion(rCAB.clave.DNI:N(8)):real

			Ambiente
				ac_cantmax:entero
			Proceso
				ac_cantmax:=0

				resperiodo:=rCAB.clave.periodo+100 // 201601 < 201613

				Mientras NFDA(arCAB) y rCAB.clave.Periodo <> resperiodo Hacer 

					rREC.Nro_Recibo:=rCAB.clave.Nro_Recibo

					Leer(arREC,rREC)

					Si Existe Entonces

						ac_cantmax:=ac_cantmax+rREC.Monto// acumulo en la salida el monto

					Fsi

					Leer(arCAB,rCAB) // paso al proximo mes

				Fm

				opcion1():=opcion1()+(ac_cantmax)

		FF

	Proceso

		AbrirE/S(arPER);
		AbrirE/S(arREC);
		AbrirE/S(arCAB);

		AbrirE/(arPET)
		AbrirS/(arSAL)

		maxARS:=0
		autorizacion:=falso

		Esc('Desea utilizar el programa v/f')
		leer(op)

		Mientras op <> 'f' hacer

			Menu() 
			leer(opn) // leo la opcion deseada

			Segun opn Hacer

				1:

					Esc('Ingrese el DNI del interesado:')
					Leer(DNIg)
					rCAB.clave.DNI:=DNIg

					rCAB.clave.Periodo:=NILL
					rCAB.clave.Nro_Recibo:=NILL // NILL PARA SECUENCIALMENTE

					leer(arCAB,rCAB)

					Si EXISTE Entonces

						sueldo:=opcion1(rCAB.clave.DNI) // (ac_cantmax*0.30) 
						maxARS:=sueldo*0.30
						maxUSD:=sueldo*0.30 / 9.4

						Si maxARS < 10000 Entonces
							Esc('No esta autorizado')
							autorizacion:=F
						Sino
							autorizacion:=V
							Esc('La persona esta autorizada a comprar la cantidad de:', maxARS ,' pesos');
							Esc('Equivalente a : $', maxUSD)
						Fsi

					Sino

						Esc('ERROR,DNI INEXISTENTE')

					Fsi

				2:

					Si autorizacion Entonces // verdadero

						Esc('Ingrese el monto de dolares a comprar:')
						Leer(monto)

						Si monto > maxUSD Entonces // 2 – Pide más del 30 % de su sueldo actual.
							rPET.DNI:=DNIg

								leer(arPET,rPET)

								Si EXISTE Entonces // 2 – Pide más del 30 % de su sueldo actual.
									rPET.Cant_Soli:=monto
									RE-ESCRIBIR(arPET,rPET)
								Sino
									rPET.Cant_Soli:=monto
									ESCRIBIR(arPET,rPET)
								Fsi

								Esc('ERROR, no dispone el saldo suficiente')
								Esc('Saldo actual:', maxUSD)

								// GRABO EN LA SAL

								rSAL.DNI:=rPET.DNI
								rSAL.Cant_Soli:=rPET.Cant_Soli
								rSAL.pudo:='no'
								rSAL.Error:=2

								Escribir(arSAL,rSAL)

						Fsi

						Si monto <> 0 Entonces

							rPER.DNI:=DNIg

							Leer(arPER,rPER)

							Si EXISTE ENTONCES

								rPER.Monto:=rPER.Monto-Monto // descontado de su cuenta el monto a comprar
								Esc('SALDO ACTUAL:', rPER.Monto)
								RE-ESCRIBIR(arPER,rPER)

							Sino
								
								Esc('Easter EGG: ERROR, EL DNI NO EXISTE, nose como llegaste hasta aca?')
								Esc('Vuelva a hacer el test de estado con un DNI valido.')
								Fsi
							Fsi

						Fsi

					Sino
						Si maxARS = 0 Entonces
							Esc('Error, todavia no hizo el test de estado')
						Sino

							rPET.DNI:=DNIg // 1 – No tiene el ingreso promedio suficiente
							leer(arPET,rPET)

							Si EXISTE Entonces // 2 – Pide más del 30 % de su sueldo actual.
								rPET.Cant_Soli:=monto
								RE-ESCRIBIR(arPET,rPET)
							Sino
								rPET.Cant_Soli:=monto
								ESCRIBIR(arPET,rPET)
							Fsi

							rSAL.DNI:=rPET.DNI
							rSAL.Cant_Soli:=rPET.Cant_Soli
							rSAL.pudo:='no'
							rSAL.Error:=1

							Escribir(arSAL,rSAL)

							Esc('No esta habilitado a comprar USD')
							Esc('Usted no cuenta con el ingreso promedio suficiente')
						Fsi
					Fsi

				3:

					rPET.DNI:=DNIg

					Leer(arPET,rPET)

					Si existe ENTONCES

						rSAL.DNI:=rPET.DNI
						rSAL.Cant_Soli:=rPET.Cant_Soli

				4:


				otros:
					Esc('ERROR, opcion invalida')

			Fs

			



			Esc('Desea utilizar nuevamente el programa v/f')
			leer(op)

		Fm


		Cerrar(arPER);
		Cerrar(arREC);
		Cerrar(arCAB);
		Cerrar(arPET);
		Cerrar(arSAL);

FA

// COD: 2H CONSIGNA 1
// COD: 46M Consigna 2
// ESTADO: Mal hecho probablemente, no entendi muy bien la consigna
// PD: mucho texto.jpg

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Ejercicio 2.3.6
Una Municipalidad debe liquidar las patentes de su parque automotor 
para el cuarto trimestre del año e imprimir un padrón de cobros y deudas,
 con 
 cortes de importe por grupo, categoría y año de fabricación.
 // CORTE DE CONTROL!!!!!!!!!! + INDEXADOS

Los archivos son:

AUTOS Ordenado por CLAVE
Grupo N(2)Categoria 1..50Anio_Fab N(4)Nro_Patente N(8)DNI AN(8)ApyNom AN(25)Domicilio AN(30)

DEUDAS Indexado por CLAVED
Nro_Patente N(8)Anio_Deuda N(4)Trimestre N(1)Importe N(5,2)

Para el trimestre actual, la cuota a abonar viene en el siguiente archivo:

CUOTAS Indexado por CLAVEC

Grupo N(2)Categoria 1..50Anio_Fab N(4)Importe N(5,2)
Antes de imprimir el renglón correspondiente a cada nro de patente 
se debe verificar si existen deudas pendientes, 
en cuyo caso se sumaran todos los importes adeudados y 
se consignarán en la columna de deudas.

PADRON

CLAVE	DNI	APYNOM	DOMIC	DEUDA	4to TRIMESTRE
.....	...	......	.....	$ XXX,XX	$ XXX,XX
TOTAL	$ XXX,XX	$ XXX,XX

Accion 2.3.6 ES

	Ambiente

		tclave = reg 

			Grupo N(2)
			Categoria 1..50
			Anio_Fab N(4)
			Nro_Patente N(8)

		fr

		tclaved = reg

			Nro_Patente N(8)
			Anio_Deuda N(4)
			Trimestre N(1)

		fr

		tclavec = reg

			Grupo N(2)
			Categoria 1..50
			Anio_Fab N(4)

		fr

		tAUTOS = reg

			clave:tclave
			DNI AN(8)
			ApyNom AN(25)
			Domicilio AN(30)

		fr

		tDEUDAS = reg

			clave:tclaved
			Importe N(5,2)

		fr

		tCUOTAS = reg

			clave:tclavec
			Importe N(5,2)

		fr

		arAUT:archivo de tAUTOS Ordenado por CLAVE
		arDEU:archivo de tDEUDAS Indexado por CLAVE
		arCUO:archivo de tCUOTAS Indexado por CLAVE

		rAUT:tAUTOS
		rDEU:tDEUDAS
		rCUO:tCUOTAS

		resgrupo,rescategoría,resAnio_Fab,ac_deuda,ac_ct,ac_gp,ac_total:entero

		Subaccion corte_grupo ES

			corte_categoria
			Esc('grupo:', res_grupo)
			Esc('importe de deuda del grupo:', ac_gp)
			ac_total:=ac_total+ac_gp
			ac_gp:=0
			res_grupo:=rAUT.clave.grupo

		Fs

		Subaccion corte_categoria ES

			corte_Anio_Fab
			Esc('categoria:', res_categoria)
			Esc('importe de deuda de la categoria:', ac_ct)
			ac_gp:=ac_gp+ac_ct
			ac_ct:=0
			resgrupo:=rAUT.clave.categoria

		Fs

		Subaccion corte_Anio_Fab ES

			//i'm here
			Esc('year de fabricación:', res_Anio_Fab)
			Esc('total importe de deuda del mismo:', ac_importe)
			ac_ct:=ac_ct+ac_importe
			ac_importe:=0
			res_Anio_Fab:=rAUT.clave.Anio_Fab

		Fs

	Proceso

		AbrirE/(arAUT,rAUT)
		AbrirE/S(arDEU,rDEU)
		AbrirE/S(arCUO,rCUO)

		ac_deuda:=0
		ac_ct:=0
		ac_gp:=0
		ac_total:=0

		Leer(arAUT,rAUT)

		resgrupo:=rAUT.clave.grupo
		rescategoría:=rAUT.clave.categoria
		resAnio_Fab:=rAUT.clave.Anio_Fab

		Mientras NFDA(arAUT) Hacer

			//tratarCDC

			//realizo los cortes
			Si resgrupo <> rAUT.grupo Entonces
				corte_grupo
			Sino

				Si rescategoría <> rAUT.categoria
					corte_categoria
				Sino

					Si resAnio_Fab <> rAUT.Anio_Fab Entonces
						corte_Anio_Fab
					Fsi

				Fsi

			Fsi

			//tratarindexados

			/*
			cuarto trimestre del año e imprimir un padrón de
			 cobros y deudas, con cortes de importe por grupo,
			  categoría y año de fabricación.
			*/

			rDEU.clave.Nro_Patente:=rAUT.clave.Nro_Patente // BUSCO SI TIENE DEUDAS LA PATENTE
			Leer(arDEU,rDEU)

			Si EXISTE Entonces

				Si rDEU.Trimestre = 4 Entonces
					ac_deuda:=ac_deuda+rDEU.importe
				Fsi

			Fsi

			////////////////////
			leer(arAUT,rAUT)

		Fm

		corte_grupo

		//IMPRIMIR TOTALES

		Cerrar(arAUT)
		Cerrar(arCUO)
		Cerrar(arDEU)

FA

//50M e INCOMPLETO NOSE COMO SEGUIR

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

