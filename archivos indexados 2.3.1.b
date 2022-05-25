archivos indexados 2.3.1.b

Dado un fichero secuencial de Facturas, ordenado por Nro. de Cliente y Nro. de Factura, con la siguiente estructura:

FACTURAS Ordenado por Nro_Cliente, Nro_Factura

Nro_ClienteNro_FacturaFechaImporte
Se desea un listado con el siguiente detalle:

Nro. Cliente	Nombre Cliente	Total Facturado	Cantidad de Facturas
Los datos del cliente se encuentran en un fichero indexado por Nro. de Cliente, que tiene la siguiente estructura:

CLIENTES Indexado por Nro_Cliente

Nro_Cliente Nombre DNI CUIT Domicilio

Accion 2.3.1.a es
	
	Ambiente
	
	f_secuencial=registro
		Nro_Cliente
		Nro_Factura
		Fecha
		Importe
	finreg

	f_indexado=registro
		Nro_Cliente 
		Nombre 
		DNI 
		CUIT 
		Domicilio
	finreg

	FACTURAS:archivo de f_secuencial ordenado por Nro_Cliente y Nro_Factura
	reg_facturas:f_secuencial

	CLIENTES:archivo de f_indexado indexado por Nro_Cliente
	reg_clientes:f_indexado

Proceso

Abrir e/(FACTURAS)
Abrir e/(CLIENTES)
Leer(FACTURAS,reg_facturas)

Mientras NFDA(FACTURAS) hacer
	
	reg_clientes.Nro_Cliente:=reg_facturas.Nro_Cliente
	Leer(CLIENTES,reg_clientes)
	res_cliente:=reg_facturas.Nro_Cliente
	totalfacturado:=0
	facturas:=0
	Mientras res_cliente = reg_facturas.Nro_Cliente hacer
		totalfacturado:=totalfacturado+reg_facturas.Importe
		facturas:=facturas+1
		Leer(FACTURAS,reg_facturas)
	finmientras
	esc("Nro.Cliente---Nombre del Cliente---Total Facturado---Cantidad de Facturas")
	esc(reg_facturas.Nro_Cliente,"---",reg_clientes.Nombre,"---",totalfacturado,"---",facturas)

finmientras