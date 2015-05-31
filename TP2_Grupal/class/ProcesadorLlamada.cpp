#include "ProcesadorLlamada.h"

ProcesadorLlamada::ProcesadorLlamada(LectorArchivos* lectorArchivosTemporal)
{
	this->datosTemporal= NULL;
	this->recorridoTemporal= NULL;
	this->centrales = new Lista<Central*>;
	this->enlaces = new Lista<Enlace*>;
	this->archivoLlamadas = lectorArchivosTemporal;
}


void ProcesadorLlamada::iniciarLlamada()
{
	// Veo si los internos existen o sino, los crea
	this->centrales->obtenerPunteroAlObjeto(this->datosTemporal->obtenerOrigen())->obtenerObjeto()->crearInterno(this->datosTemporal->obtenerEmisor() );
	this->centrales->obtenerPunteroAlObjeto(this->datosTemporal->obtenerDestino())->obtenerObjeto()->crearInterno(this->datosTemporal->obtenerReceptor() );

	//Obtengo punteros a cada interno
	Interno* emisor;
	Interno* receptor;

	emisor = this->centrales->obtenerPunteroAlObjeto(this->datosTemporal->obtenerOrigen() )->obtenerObjeto()->obtenerInterno(this->datosTemporal->obtenerEmisor() );
	receptor = this->centrales->obtenerPunteroAlObjeto(this->datosTemporal->obtenerDestino() )->obtenerObjeto()->obtenerInterno(this->datosTemporal->obtenerReceptor() );

	//Agrego la llamada a cada interno
	emisor->agregarLlamadaEmisor(this->datosTemporal->obtenerReceptor(), this->datosTemporal->obtenerHora(), this->recorridoTemporal->obtenerRuta() );
	receptor->agregarLlamadaReceptor(this->datosTemporal->obtenerEmisor(), this->datosTemporal->obtenerHora(), this->recorridoTemporal->obtenerRuta() );

	//Cambio la disponibilidad de los enlaces
	//Cambio disponibilidad de enlaces
	Lista<Enlace*>* enlacesRecorridos = emisor->devolverRecorridoLlamada(this->datosTemporal->obtenerReceptor() );
	enlacesRecorridos->iniciarCursorNodo();

	while( enlacesRecorridos->avanzarCursorNodo() )	{
		enlacesRecorridos->obtenerCursorNodo()->agregarLlamadaEnCurso();
	}
}

void ProcesadorLlamada::finalizarLlamada()
{
	//Obtengo punteros a cada interno
	Interno* emisor;
	Interno* receptor;
	
	emisor = this->centrales->obtenerPunteroAlObjeto(this->datosTemporal->obtenerOrigen() )->obtenerObjeto()->obtenerInterno(this->datosTemporal->obtenerEmisor() );
	receptor = this->centrales->obtenerPunteroAlObjeto(this->datosTemporal->obtenerDestino() )->obtenerObjeto()->obtenerInterno(this->datosTemporal->obtenerReceptor() );
	
	// Termino la llamada en cada interno
	emisor->terminarLlamadaEmisor(this->datosTemporal->obtenerEmisor(), this->datosTemporal->obtenerHora(), this->recorridoTemporal->obtenerPrecioDeLaLlamada() );
	receptor->terminarLlamadaReceptor(this->datosTemporal->obtenerReceptor(), this->datosTemporal->obtenerHora(), this->recorridoTemporal->obtenerPrecioDeLaLlamada() );

	//Cambio disponibilidad de enlaces
	Lista<Enlace*>* enlacesRecorridos = emisor->devolverRecorridoLlamada(this->datosTemporal->obtenerReceptor()) ;
	enlacesRecorridos->iniciarCursorNodo();

	while( enlacesRecorridos->avanzarCursorNodo() ) {
		enlacesRecorridos->obtenerCursorNodo()->eliminarLlamadaEnCurso();
	}
}

void ProcesadorLlamada::agregarCentral(int numeroCentral)
{
	this->centrales->iniciarCursorNodo();
	bool encontro=false;
	while ((this->centrales->avanzarCursorNodo()) && (! encontro)) {
		encontro= (numeroCentral == this->centrales->obtenerCursorNodo()->obtenerNumero()) ;
	}
	if (! encontro) {
		Central* nuevaCentral= new Central(numeroCentral) ;
		this->centrales->insertar(nuevaCentral);

	}
}

void ProcesadorLlamada::agregarEnlace(int numeroOrigen, int numeroDestino)
{
	this->enlaces->iniciarCursorNodo();
	bool encontro=false;
	while ((this->enlaces->avanzarCursorNodo()) && (! encontro)) {
		encontro= ( numeroOrigen == this->enlaces->obtenerCursorNodo()->obtenerOrigen()->obtenerNumero() )
		          &&
		          ( numeroDestino == this->enlaces->obtenerCursorNodo()->obtenerDestino()->obtenerNumero() ) ;
	}
	if (! encontro) {
		// Aca tener en cuenta que los atributos de this->datosTemporal siguen con los nombres como si fuera
		// una llamada, pero realmente es para una enlace y estan ordenados
		Enlace* nuevoEnlace = new Enlace(numeroOrigen, numeroDestino, this->datosTemporal->obtenerDestino(),
		                                 this->datosTemporal->obtenerReceptor(), this->datosTemporal->obtenerHora(), this->centrales);

		this->enlaces->insertar(nuevoEnlace);

		//Agrego el puntero a
		this->centrales->iniciarCursorNodo();

		while ( this->centrales->avanzarCursorNodo() ) {
			Central* centralTemporal = this->centrales->obtenerCursorNodo();

			if (centralTemporal->obtenerNumero() == numeroDestino || centralTemporal->obtenerNumero() == numeroOrigen) {
				centralTemporal->agregarEnlace(nuevoEnlace);
			}

		}
	}
}

Lista<Central*>* obtenerCentrales()
{
	return this->centrales;
}

Lista<Enlace*>* obtenerEnlaces()
{
	return this->enlaces;
}

void ProcesadorLlamada::procesarLlamadas()
{
	while ( archivoLlamadas->chequearLlamadas() ) {
		this->datosTemporal = archivoLlamadas->obtenerDatosLlamada();

		this->agregarCentral(this->datosTemporal->obtenerOrigen() );
		this->agregarCentral(this->datosTemporal->obtenerDestino() );

		if ( this->datosTemporal->obtenerAccion() == "Inicio") {
			// Aca va el tema con el buscador de caminos
			// recorridoTemporal = this->buscaCentral;
			this->iniciarLlamada();
		} else {
			if ( this->datosTemporal->obtenerAccion() == "Fin") {
				this->finalizarLlamada();
			} else {
				if ( this->datosTemporal->obtenerAccion() == "Enlace") {
					agregarEnlace(this->datosTemporal->obtenerOrigen(), this->datosTemporal->obtenerDestino());
				}
			}
		}
	}
}