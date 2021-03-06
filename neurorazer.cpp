//      by Tijuinem :   tijuinem -at- gmail -dot- com                   
//      NeuroRAZER versi�n "ESTANDAR". Clon-versi�n libre del juego Neuroracer, poni�ndolo algo m�s dif�cil; uso del rat�n. 
//      NeuroraZer es un videojuego creado para mejorar el rendimiento cognitivo.

//      Indice de versiones:
//      versi�n alfa 1.0  09-12-2013                                    //version modo local
//      versi�n alfa 1.1  11-12-2013                                    //carga pantallas ok.                                              
//      versi�n alfa 1.2  12-12-2013                                    //desde esta versi�n se libera el c�digo en github. se permite editar, borrar, coger, fork... aunque se agradecer�n ampliaciones y mejoras.
//      versi�n alfa 1.3  16-12-2013                                    //incrementos de velocidades. puntos.
//      versi�n alfa 1.4  17-12-2013                                    //aparicion o no de bicis, coches, y segunda tarea.
//      versi�n Beta 1.0  18-12-2013                                    //primera versi�n jugable p�blica. 
//      versi�n Beta 1.1  23-12-2013                                    //ahora tambi�n con camiones ...
//      versi�n Beta 1.2  01-01-2014                                    //incrementar/decrementar vechiculos. quitar/poner tareas.
//      versi�n Beta 1.3  13-01-2014                                    //incrementar/decrementar velocidades. archivo help. aleatorios
//      versi�n Beta 1.4  13-01-2014                                    //subo ya una version EXE a sourceforge

       char version_ultima[50] = "version Beta 1.4  14-01-2014";        //actualizar aqui la versi�n a la hora de compilar
       char programadores[600] = "tijuinem at gmail dot com";           //a�ade tu nombre o mail, para aparecer actualizado en los cr�ditos :)

/*   ______   ___    ___
    /\  _  \ /\_ \  /\_ \
    \ \ \ \ \\//\ \ \//\ \      __     __   _ __   ___
     \ \  __ \ \ \ \  \ \ \   /'__`\ /'_ `\/\`'__\/ __`\
      \ \ \/\ \ \_\ \_ \_\ \_/\  __//\ \ \ \ \ \//\ \ \ \
       \ \_\ \_\/\____\/\____\ \____\ \____ \ \_\\ \____/
        \/_/\/_/\/____/\/____/\/____/\/___ \ \/_/ \/___/
                                       /\____/
                                       \_/__/     Versi�n 4 */                                     
//------------------------------------------------------------------------------globales
#include <allegro.h>

 int fondo_pantalla = 0;
 int fin_juego = 0;
 BITMAP *fondo1, *fondo2, *fondo3, *fondo4, *fondo5, *fondo6, *fondo7, *fondo8, *fondo9;
 BITMAP *portada_y_salida, *coches_extra, *bicis_extra, *camiones_extra;
 BITMAP *coches_extra_doble_buffer, *bicis_extra_doble_buffer, *camiones_extra_doble_buffer;
 PALLETE paleta;
 long int puntos_ppal = 0;
 long int vida_ppal = 4664;                                                     //homenaje a N.M. 
 int velocidad_scroll = 1;                                                      //aconsejable si no funciona el fps.
 int balas = 100;
 int pantallas_recorridas =0;
 int size_coche_y = 100, size_coche_x = 50; 
 int size_mapa_x = 640, size_mapa_y = 8000;
 bool mostramos_coches=false, mostramos_bicis =false, mostramos_camiones = false;
 int numero_coches_a_incrementar =0, numero_bicis_a_incrementar =0 ,numero_camiones_a_incrementar =0; 
 bool activar_punto_rojo = false, activar_punto_amarillo=false;
 char esto_es_si_bicis [25]=      "BICIS      (F3/F4)",         esto_es_no_bicis [30]= "BICIS    NO(F3/F4)";
 char esto_es_si_coches [25]=     "COCHES     (F5/F6)",        esto_es_no_coches [30]= "COCHES   NO(F5/F6)"; 
 char esto_es_si_camiones [25]=   "CAMIONES   (F7/F8)",      esto_es_no_camiones [30]= "CAMIONES NO(F7/F8)"; 
 char esto_es_si_p_rojo [25]=     "P.ROJO     SI(F9)",         esto_es_no_p_rojo [30]= "P.ROJO     NO(F9)";
 char esto_es_si_p_amarillo [25]= "P.AMARILLO SI(F10)",    esto_es_no_p_amarillo [30]= "P.AMARILLO NO(F10)";
 
//------------------------------------------------------------------------------cargo ficheros externos
#include "carga_pantallas.h" 
#include "presentacion.h"
#include "salida.h" 
#include "coches_a_mostrar.h"

//------------------------------------------------------------------------------modo grafico del juego
#define modo_pantallaX  640                                                     //modo seleccionado para que funcione en cualquier ordenador por obsoleto que est�. como mi 386 XD
#define modo_pantallaY 480
#define numero_de_bits 16 

//-------temporizadores---------------------------------------------------------temporizadores------------  
  volatile int cuenta_atras;
      void mi_temporizador()
      {            
      cuenta_atras--; 
      }
      END_OF_FUNCTION(mi_temporizador);  
//------------------------------------------------------------------------------main-----------  
void main(void)
{ 
//------------------------------------------------------------------------------variables generales generales y configuraciones b�sicas 
 allegro_init();                                                                //Initialize Allegro.  
 set_color_depth(numero_de_bits);                                               //selecciono X bits
 set_gfx_mode(GFX_SAFE, modo_pantallaX , modo_pantallaY, 0, 0);                 //Set the resolution  with SAFE autodetection.
 install_keyboard();  
 install_timer(); 
 srand(time(NULL));

//------------------------------------------------------------------------------tema raton
 install_mouse();
 BITMAP *punto_mira, *punto_mira_disparado;
 PALLETE paleta;
 punto_mira = load_bitmap ("graficos/punto_mira1.pcx", paleta);
 punto_mira_disparado = load_bitmap ("graficos/punto_mira_disparo.pcx", paleta);
 scare_mouse();
 clear_bitmap(screen);
 scare_mouse();                                                                 /*oculto raton*/
 //unscare_mouse();                                                             /*no oculto raton*/
 //show_mouse(screen);                                                          //dibujo el raton basico . quito el raton normal
 //show_mouse(punto_mira);

//-------temporizadores------------------------------------------------------temporizadores------------   
   LOCK_VARIABLE(contador);
   LOCK_FUNCTION(mi_temporizador);        
                                         
//------------------------------------------------------------------------------cargo  graficos
 clear_keybuf(); // Borra el buffer del teclado 
 acquire_screen(); // Bloquea screen antes de dibujar en �l, screen es el BITMAP por donde nos moveremos 
 fondo1 = load_bitmap ("graficos/recta 640 8000 verde.pcx", paleta); 
 fondo2 = load_bitmap ("graficos/recta 640 8000 gris.pcx", paleta); 
 fondo3 = load_bitmap ("graficos/recta 640 8000 estrechamiento.pcx", paleta); 
 fondo4 = load_bitmap ("graficos/recta 640 8000 curva1.pcx", paleta);
 fondo5 = load_bitmap ("graficos/recta 640 8000 curva2.pcx", paleta); 
 fondo6 = load_bitmap ("graficos/recta 640 8000 curva3.pcx", paleta);
 fondo7 = load_bitmap ("graficos/recta 640 8000 curva4.pcx", paleta); 
 fondo8 = load_bitmap ("graficos/recta 640 8000 puente.pcx", paleta); 
 fondo9 = load_bitmap ("graficos/recta 640 8000 mar.pcx", paleta); 

//------------------------------------------------------------------------------coches en la carretera
 coches_extra = load_bitmap   ("graficos/6coches50pixels-ancho.pcx", paleta);     //prueba con fondo fucsia. si con draw. no con blit.
 bicis_extra  = load_bitmap   ("graficos/6bicis50pixels-ancho.pcx",  paleta);     //cada bici tiene 50*100. hay 6 .
 camiones_extra = load_bitmap ("graficos/7camiones100pixels-ancho.pcx", paleta);

//------------------------------------------------------------------------------coche ppal. mejorar con struct
 int coordX = 300 , coordY= 300 ;                                               //posicion de salida
 int incremento_coordenadas = 1;  
 int fondoX = 0 , fondoY= 0 ;                                                   //colores de fondo por defecto NEGRO
 int limite_pantalla_X = modo_pantallaX - size_coche_x, limite_pantalla_Y  = modo_pantallaY - size_coche_y; //limites de pantalla para el objeto.
 BITMAP *cochePPAL, *doble_buffer_cochePPAL ;                                   //doble buffer para el coche ppal. ???
 cochePPAL = load_bitmap ("graficos/coche316bitsFUCSIA.pcx", paleta); 
 doble_buffer_cochePPAL = create_bitmap(50,100);                                //si funciona , meter mas coches
//------------------------------------------------------------------------------para coger los colores que rodean al coche   
 int color_en_x_coche_arriba_decha;   
 int color_en_x_coche_arriba_izda;
 int color_en_y_coche_abajo_decha;   
 int color_en_y_coche_abajo_izda;  

//------------------------------------------------------------------------------preparando scroll
 int recorre_y =0;
 int retraso_pintar = 1;                                                        //1 si no FPS
 int size_pantalla_mostar = 480;
 int pantallas_en_disco = 10;
 bool activa_titulo_vida_extra = false;

//------------------------------------------------------------------------------sonido
 SAMPLE *choque;
 SAMPLE *motor1;
    if (install_sound(DIGI_AUTODETECT, MIDI_NONE, "") != 0) 
    {
        allegro_message("problema tarjeta sonido");
        return;
    }
//------------------------------------------------------------------------------carga del archivo de sonido
    choque = load_sample("sonido/choque_pared.wav");
    motor1 = load_sample("sonido/motor1.wav");
    if ((!choque) || (!motor1))
    {
        allegro_message("no encuentro el archivo de audio");
        return;
    }   
//------------------------------------------------------------------------------para usar aleatorios
  int aleatorio;
  int dificultad_aleatorio = 5000;
  int x_aleatorio, y_aleatorio;
  bool punto_rojo_en_pantalla = false, punto_amarillo_en_pantalla = false; 
  BITMAP *punto_rojo, *punto_amarillo,; //con doble buffer igual pq trabajo sobre screen, no fondo.                                  
  punto_rojo = load_bitmap ("graficos/punto_rojo.pcx", paleta);
  punto_amarillo = load_bitmap ("graficos/punto_amarillo.pcx", paleta);

  
//------------------------------------------------------------------------------programacion ppal del juego   
 PRESENTACION ();
 carga_pantalla (fondo_pantalla);
 if (mostramos_bicis    == true ) {bicis_a_mostrar    (6); }
 if (mostramos_coches   == true ) {coches_a_mostrar   (6); }
 if (mostramos_camiones == true)  {camiones_a_mostrar (7); }
 install_int(mi_temporizador, 1000);
do
{ 

 if (recorre_y <= size_mapa_y + modo_pantallaY )
  {
      recorre_y = recorre_y + velocidad_scroll;
      blit(fondo1, screen, 0, size_mapa_y - modo_pantallaX  - recorre_y , 0, 0, modo_pantallaX , modo_pantallaY );       //la primera pantalla empieza en el tama�o del mapa menos 480.
      //textprintf(screen, font, 10,10, palette_color[12], "recorre_y  %d",recorre_y );
      //textprintf(screen, font, 10,20, palette_color[12], "pantalla  %d", fondo_pantalla);
      //textprintf(screen, font, 10,200, palette_color[12], "incremento_coordenadas  %d", incremento_coordenadas);
      //textprintf(screen, font, 10,220, palette_color[12], "dificultad_aleatorio  %d", dificultad_aleatorio);
            
      textprintf(screen, font, 10,5,  palette_color[12], "VIDA      %d", vida_ppal);
      textprintf(screen, font, 10,15, palette_color[12], "PUNTOS    %d", puntos_ppal);
      textprintf(screen, font, 10,25, palette_color[12], "BALAS     %d", balas); 
      textprintf(screen, font, 10,35, palette_color[14], "==================", velocidad_scroll);
      textprintf(screen, font, 10,45, palette_color[14], "                %d", velocidad_scroll);
      textprintf(screen, font, 10,45, palette_color[12], "VELOCIDAD F1/F2:");
      textprintf(screen, font, 10,105,palette_color[12], "TURBO/FRENO F11/F12");
     
      if (mostramos_bicis == true) 
         { textout(screen, font, esto_es_si_bicis, 10, 55, palette_color[12]);
           textprintf(screen, font, 75,55, palette_color[14], "=%d ", numero_bicis_a_incrementar *6); } 
         else {textout(screen, font, esto_es_no_bicis, 10, 55, palette_color[9]);}
      if (mostramos_coches == true) 
         { textout(screen, font, esto_es_si_coches, 10, 65, palette_color[12]);
           textprintf(screen, font, 75, 65, palette_color[14], "=%d ", numero_coches_a_incrementar *6);   } 
         else {textout(screen, font, esto_es_no_coches, 10, 65, palette_color[9]);}
      if (mostramos_camiones == true) 
         { textout(screen, font, esto_es_si_camiones, 10, 75, palette_color[12]);  
           textprintf(screen, font, 75, 75, palette_color[14], "=%d ", numero_camiones_a_incrementar *7); } 
         else {textout(screen, font, esto_es_no_camiones, 10, 75, palette_color[9]);}
      if (activar_punto_rojo == true) 
         { textout(screen, font, esto_es_si_p_rojo, 10, 85, palette_color[12]);   } 
         else {textout(screen, font, esto_es_no_p_rojo, 10, 85, palette_color[9]);}
      if (activar_punto_amarillo == true) 
         { textout(screen, font, esto_es_si_p_amarillo, 10, 95, palette_color[12]);   } 
         else {textout(screen, font, esto_es_no_p_amarillo, 10, 95, palette_color[9]);} 
      
      blit(cochePPAL , doble_buffer_cochePPAL, 0, 0 , 0, 0, size_coche_x, size_coche_y );           //con doble buffer. ventaja que cojo cachos.
      draw_sprite(screen, doble_buffer_cochePPAL, coordX, coordY); 
      //draw_sprite(screen, cochePPAL, coordX, coordY);                          //formato simple buffer. resultados similares. velocidad mas lenta. ademas aqui trabajo cogiendo puntos de color.
         
//------------------------------------------------------------------------------cambio pantalla. y dibujos aleatorios 
 if ( (recorre_y >= size_mapa_y  ) &&  (fin_juego == 0)) 
          {
          fondo_pantalla =  rand() % pantallas_en_disco ;                       //cojo una pantalla aleatoria
          recorre_y = - modo_pantallaY;
          pantallas_recorridas ++;
          size_pantalla_mostar = 0;
          activa_titulo_vida_extra = true ;
          cuenta_atras = 2;  
          vida_ppal = vida_ppal + 100;                     
          carga_pantalla (fondo_pantalla);
          if (mostramos_bicis  == true )                                        //lamo a los vehiculos a mostrar tantas veces como vaya marcando. cada vez, 6 coches.
              {
              for (int nbi=1; nbi <= numero_bicis_a_incrementar; nbi ++)
                  { bicis_a_mostrar  (6);}
              }
          if (mostramos_coches == true ) 
              {
              for (int nci=1; nci <= numero_coches_a_incrementar; nci ++)
                  { coches_a_mostrar  (6);}              
              }
          if (mostramos_camiones == true ) 
              {
              for (int ncci=1; ncci <= numero_camiones_a_incrementar; ncci ++)
                  { camiones_a_mostrar  (7);}              
              }
          x_aleatorio = rand() % 550;                                           //para mostrar el punto rojo en diferentes sitios en cada circuito
          y_aleatorio = rand() % 375;                          
          }
           
//------------------------------------------------------------------------------activa_titulos_vida_extra ---avisos de reloj------
    if (activa_titulo_vida_extra == true  || cuenta_atras >=1 )
          {    
          textprintf(screen, font, 200,100, palette_color[15], " + 100 puntos de vida Extra");
          textprintf(screen, font, 200,120, palette_color[15], "        Pantalla %d        " , pantallas_recorridas);          
          activa_titulo_vida_extra = false;                    
          }  
//------------------------------------------------------------------------------movimiento del coche. limites------------        
       if (key[KEY_ESC] || (fin_juego == 1))  //escape de juego
           {
           fin_juego = 1;
           clear_keybuf();                 
           }
        if (key[KEY_LEFT]) 
         if (coordX >= 0 + size_coche_x/4)   { coordX = coordX - incremento_coordenadas;  }
        if (key[KEY_RIGHT]) 
         if (coordX <= limite_pantalla_X  - size_coche_x/4) { coordX = coordX + incremento_coordenadas; }   
        if (key[KEY_UP]) 
         if (coordY >= 0 + size_coche_y/4 )  { coordY = coordY - incremento_coordenadas; }              
        if (key[KEY_DOWN]) 
         if (coordY <= limite_pantalla_Y - size_coche_y/4 )  { coordY = coordY + incremento_coordenadas; }  

//--------------------------------------------------------------------------aleatorio mostrar avisos--------------
  aleatorio =  rand() % dificultad_aleatorio;
  if (( aleatorio == 69 ) && (activar_punto_rojo==true)) {  punto_rojo_en_pantalla = true;  }
  if ( punto_rojo_en_pantalla == true ) 
  { 
  draw_sprite(screen, punto_rojo, x_aleatorio, y_aleatorio); 
  play_sample(choque, 255, 0, 2000, FALSE); 
  vida_ppal -- ;
  }
  
  if (( aleatorio == 666 ) && (activar_punto_amarillo == true)) {  punto_amarillo_en_pantalla = true;  }
  if ( punto_amarillo_en_pantalla == true ) 
  {   
  draw_sprite(screen, punto_amarillo, x_aleatorio, y_aleatorio); 
  play_sample(choque, 255, 0, 3000, FALSE); 
  vida_ppal -- ;
  }  
  
//------------------------------------------------------------------------tema raton. le doy x pixels para que detecte posicion.
    if ( activar_punto_rojo== true){
    switch (mouse_b)
      {
      case 0:
      draw_sprite(screen, punto_mira, mouse_x, mouse_y);   
      break ;
      case 1:
      draw_sprite(screen, punto_mira_disparado, mouse_x, mouse_y);
      play_sample(choque, 255, 255, 1700, FALSE);                               
      balas --;
      break ;
      default: 
      draw_sprite(screen, punto_mira, mouse_x, mouse_y); 
      }      
   if((mouse_b & 1) &&
     (punto_rojo_en_pantalla == 1 ) &&
     (mouse_x >= x_aleatorio +20) && (mouse_x <= x_aleatorio +40) && 
     (mouse_y >= y_aleatorio +20) && (mouse_y <= y_aleatorio +40))
       {         
       mouse_b  = 0;
       punto_rojo_en_pantalla = 0;
       balas = balas + 15;
       }
   }   
   if ((key[KEY_SPACE]) && (punto_amarillo_en_pantalla == true))
   {punto_amarillo_en_pantalla = false;}

//------------------------------------------------------------------------------colores que rodean al coche. para choques
  color_en_x_coche_arriba_izda =  _getpixel16 (screen, coordX , coordY);          //probado tambien con _getpixel16 y _getpixel . 
  color_en_x_coche_arriba_decha = _getpixel16 (screen, coordX + size_coche_x, coordY);
  color_en_y_coche_abajo_izda =   _getpixel16 (screen, coordX , coordY + size_coche_y);
  color_en_y_coche_abajo_decha =  _getpixel16 (screen, coordX + size_coche_x , coordY + size_coche_y );   
       
//------------------------------------------------------------------------------fuera / dentro del circuito 
  if( (color_en_x_coche_arriba_izda  == 0 )  
  &&  (color_en_x_coche_arriba_decha == 0 ) 
  &&  (color_en_y_coche_abajo_izda   == 0 )  
  &&  (color_en_y_coche_abajo_decha  == 0 ) 
  &&  (fin_juego == 0) )
  {
  puntos_ppal ++;  
  }
  else 
     { 
      //textout(screen, font, "estas fuera del circuito", 160,80, palette_color[15]);
      if (coordX  >= 320 ) {  play_sample(choque, 255, 255, 1000, FALSE); }
      if (coordX  <= 320 ) {  play_sample(choque, 255, -255, 1000, FALSE); }
      vida_ppal --;
     }    
     
//-----------------------------------------------------------------------------puntos, vida , salida , incrementos.
  if (keypressed()) 
  {
    switch (readkey() >> 8) 
    {
        case KEY_F1:
            velocidad_scroll ++;
            break;
        case KEY_F2:
            if ( velocidad_scroll < 1) 
            { velocidad_scroll = 1; puntos_ppal --;}
            velocidad_scroll --;
            break;
        case KEY_F3:
            numero_bicis_a_incrementar ++;
            mostramos_bicis =   true;
            break;
        case KEY_F4:
            numero_bicis_a_incrementar --;
            if (numero_bicis_a_incrementar <= 0) 
            {numero_bicis_a_incrementar=0; mostramos_bicis = false;}
            break;
        case KEY_F5:
            numero_coches_a_incrementar ++;
            mostramos_coches =  true;
            break;
        case KEY_F6:
            numero_coches_a_incrementar --;
            if (numero_coches_a_incrementar <= 0) 
            {numero_coches_a_incrementar=0; mostramos_coches = false;}
            break;
        case KEY_F7:
            numero_camiones_a_incrementar ++;
            mostramos_camiones =  true;
            break;
        case KEY_F8:
            numero_camiones_a_incrementar --;
            if (numero_camiones_a_incrementar <= 0) 
            {numero_camiones_a_incrementar=0; mostramos_camiones = false;}
            break;
        case KEY_F9:
            if (activar_punto_rojo==true ) {activar_punto_rojo = false;} 
            else if (activar_punto_rojo == false) {activar_punto_rojo = true;}
            break;                 
        case KEY_F10:
            if (activar_punto_amarillo==true ) {activar_punto_amarillo = false;} 
            else if (activar_punto_amarillo == false) {activar_punto_amarillo = true;}
            break;
        case KEY_F11:
            retraso_pintar -- ;
            if (retraso_pintar <= 0) {retraso_pintar=0;}
            break;
        case KEY_F12:
            retraso_pintar ++;
            break;
        case KEY_MINUS_PAD:
            if (incremento_coordenadas <= 1 )     {incremento_coordenadas = 1;} 
            else if (incremento_coordenadas != 0) {incremento_coordenadas --;}                                    
            break;  
        case KEY_PLUS_PAD:
            incremento_coordenadas ++;   
            if (incremento_coordenadas >= 20) {incremento_coordenadas = 20;}                                       
            break;
        case KEY_A:
            dificultad_aleatorio = 1000;                                                          
            break;
        case KEY_P:
            if (velocidad_scroll == 0 ) {velocidad_scroll = 1;} 
            else if (velocidad_scroll != 0) {velocidad_scroll = 0;}                                                         
            break;
        case KEY_U:
            puntos_ppal= puntos_ppal + 1000;                                    //haciendo trampas 
            break;
    }
  }    
  //----------------------------------------------------------------------------trampas y puntos
  
  if (pantallas_recorridas >= 99 ) 
          {   
          mostramos_camiones = true;
          numero_camiones_a_incrementar =1;
          mostramos_bicis =   true;
          numero_bicis_a_incrementar =1;
          mostramos_coches =  true;
          numero_coches_a_incrementar =1;
          activar_punto_rojo = true;
          activar_punto_amarillo= true;
          }
  if ( (puntos_ppal > 1000000) ) { velocidad_scroll = 10; }
  if ( (puntos_ppal > 2000000) ) { velocidad_scroll = 25; }
  if ( (puntos_ppal > 3000000) )  { retraso_pintar = 0; }                
  if (  vida_ppal <= 0 ) { 
        fin_juego = 1; textout(screen, font, 
        "Vida principal terminada. FIN de JUEGO", 200,200, palette_color[15]); 
        rest (2000); 
        SALIDA(); }

rest (retraso_pintar);     
 } //--------------------------------------------------------------------------fin del ciclo for de recorrer fondos y juego
} while (fin_juego==0);//------------------------------------------------------fin juego
 SALIDA ();
//------------------------------------------------------------------------------salir de allegro, con alegr�a.
 poll_keyboard(); // no deberia ser necesario , pero parece que lo es.
 clear_keybuf();
 allegro_exit();
//------------------------------------------------------------------------------destruyo todas las memorias graficas
 destroy_bitmap(fondo1);
 destroy_bitmap(fondo2);
 destroy_bitmap(fondo3);
 destroy_bitmap(fondo4);
 destroy_bitmap(fondo5);
 destroy_bitmap(fondo6);
 destroy_bitmap(fondo7);
 destroy_bitmap(fondo8);
 destroy_bitmap(fondo9);
 destroy_bitmap(cochePPAL);
 destroy_bitmap(punto_mira);
 destroy_bitmap(punto_mira_disparado);
 destroy_bitmap(portada_y_salida);
 destroy_bitmap(coches_extra);
 destroy_bitmap(bicis_extra);
 destroy_bitmap(camiones_extra); 
//------------------------------------------------------------------------------destruyo todas las memorias audio
 destroy_sample(choque);
 destroy_sample(motor1);
//------------------------------------------------------------------------------remove the sound driver
 remove_sound();
return ;     
}     
END_OF_MAIN();
