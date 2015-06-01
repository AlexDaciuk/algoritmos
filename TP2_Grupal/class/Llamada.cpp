

#include "Llamada.h"

Llamada::Llamada (int receptorLlamadaTemporal)
{
	if ((receptorLlamadaTemporal > 0) && (receptorLlamadaTemporal <= 9999)) {
		this->cantidadLlamadasHechas = 0;
		this->cantidadLlamadasRecibidas = 0;
		this->duracionLlamadasHechas = 0;
		this->duracionLlamadasRecibidas = 0;
		this->cantidadOcupadosDados = 0;
		this->cantidadOcupadosRecibidos = 0;
		this->horaInicioLlamadaEnCurso =0;
		this->llamadasAnuladas = 0;
		this->receptorLlamada = receptorLlamadaTemporal;
		this->recorridoLlamada = NULL;
	}
}

void Llamada::empezarLlamadaEmisor(int horaInicioLlamadaEnCursoTemporal, Lista<Enlace*>* recorridoLlamadaTemporal)
{
	this->cantidadLlamadasHechas++;
	this->horaInicioLlamadaEnCurso = horaInicioLlamadaEnCursoTemporal;
	this->recorridoLlamada = recorridoLlamadaTemporal;
}

void Llamada::empezarLlamadaReceptor(int horaInicioLlamadaEnCursoTemporal, Lista<Enlace*>* recorridoLlamadaTemporal)
{
	this->cantidadLlamadasRecibidas++;
	this->horaInicioLlamadaEnCurso = horaInicioLlamadaEnCursoTemporal;
	this->recorridoLlamada = recorridoLlamadaTemporal;
}

void Llamada::cortarLlamadaEmisor(int horaFinLlamadaEnCursoTemporal, int precioMinuto)
{
	this->costoLlamadas += (horaFinLlamadaEnCursoTemporal - this->horaInicioLlamadaEnCurso) * precioMinuto;
	this->duracionLlamadasHechas += (horaFinLlamadaEnCursoTemporal - this->horaInicioLlamadaEnCurso);
	this->horaInicioLlamadaEnCurso = 0;
	this->recorridoLlamada = NULL;
}

void Llamada::cortarLlamadaReceptor(int horaFinLlamadaEnCursoTemporal, int precioMinuto)
{
	this->costoLlamadas += (horaFinLlamadaEnCursoTemporal - this->horaInicioLlamadaEnCurso) * precioMinuto;
	this->duracionLlamadasRecibidas += (horaFinLlamadaEnCursoTemporal - this->horaInicioLlamadaEnCurso);
	this->horaInicioLlamadaEnCurso = 0;
	this->recorridoLlamada = NULL;
}

int Llamada::obtenerLlamadasAnuladas()
{
  return this->llamadasAnuladas;
}

int Llamada::obtenerReceptorLlamada()
{
	return this->receptorLlamada;
}

int Llamada::obtenerCantidadLlamadasRecibidas()
{
	return this->cantidadLlamadasRecibidas;
}

int Llamada::obtenerDuracionLlamadasRecibidas()
{
	return this->duracionLlamadasRecibidas;
}

int Llamada::obtenerDuracionLlamadasHechas()
{
	return this->duracionLlamadasHechas;
}

int Llamada::obtenerCantidadOcupadosDados()
{
	return this->cantidadOcupadosDados;
}

int Llamada::obtenerCantidadOcupadosRecibidos()
{
	return this->cantidadOcupadosRecibidos;
}

int Llamada::obtenerCantidadLlamadasHechas()
{
	return this->cantidadLlamadasHechas;
}

int Llamada::obtenerCostoLlamadas()
{
	return this->costoLlamadas;
}

Lista<Enlace*>* Llamada::obtenerRecorridoLlamada()
{
	return this->recorridoLlamada;
}

void Llamada::agregarOcupadoRecibido()
{
	this->cantidadOcupadosRecibidos++;
}

void Llamada::agregarOcupadoDado()
{
	this->cantidadOcupadosDados++;
}

void Llamada::contarLlamadaAnulada()
{
  this->llamadasAnuladas++;
}



