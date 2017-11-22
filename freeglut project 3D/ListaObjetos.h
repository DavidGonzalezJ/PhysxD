

#ifndef _LISTAOBJETOS_
#define _LISTAOBJETOS_


#include <stdlib.h>
template <class T>
//clase lista con enlace simple circular y P.I que utiliza plantillas
//la lista tiene long+1 nodos donde el 1º de ellos es el puntoMaximal
//el cual es mayor que todos los demas el punto de interes apunta al
//nodo anterior al ultimo nodo accedido
//La insercion de elementos se realiza por copia(borrar elementos insertados)
class tLista{
        private:
                class tNodo{
                private:
                        friend class tLista<T>;
                        T _info;
                        tNodo* _sig;
						tNodo* _ant;
                };
                class tPuntoInteres{
                private:
                        friend class tLista<T>;
                        tNodo* _pCur;
                        int _ind;
                };
                tNodo* _pCab;
				tNodo* _pUlt;
                tPuntoInteres* _pi;
                int _long;
				void _avanza();
				void _retrocede();
                void _reinicia();
				void _goEnd();
				bool _buscaPos(int pos);
        public:
                
                ~tLista(); //destructora
                tLista(); //constructora por defecto
                tLista(tLista<T>& t); //constructora por copia
                int _length();
                
                
                bool _add(T info);
                bool _remove(int pos);
				bool _remove(T info);
                bool _get(int num,T& info);
				bool _getPointer(int num,T*& info);
       
};
//----------------------------------------------------------------------------
        template <class T>
        tLista<T>::tLista(){
            _long=0;
            _pCab=NULL;          
			_pUlt=NULL;          
            _pi = NULL;
        }
//----------------------------------------------------------------------------
        template <class T>
        tLista<T>::tLista(tLista<T>& t){
            T elem;
            T aux;
            _long=0;     

            for (int i=0;i<t._long;i++){
                t._get(i,aux);
                copia(elem,aux);
                this->_add(elem);
            }
        }
//----------------------------------------------------------------------------
        template <class T>
        tLista<T>::~tLista(){
            T elem;
            int cont=_long;
            for (int i=cont-1;i>=0;i--){
                    _get(0,elem);
                    _remove(0);
                    eliminaDato(elem);
            }
            delete _pCab;
			delete _pUlt;
            delete _pi;
        }
//----------------------------------------------------------------------------
        template <class T>
        int tLista<T>::_length(){
            return _long;
        }
//----------------------------------------------------------------------------
        template <class T>
        void tLista<T>::_avanza(){
            _pi->_ind++;
            _pi->_pCur=_pi->_pCur->_sig;
        }

//----------------------------------------------------------------------------
        template <class T>
        void tLista<T>::_retrocede(){

            _pi->_ind--;
            _pi->_pCur=_pi->_pCur->_ant;
			
        }
//---------------------------------------------------------------------------
        template <class T>
        void tLista<T>::_reinicia(){
                _pi->_ind=0;
                _pi->_pCur=_pCab;
        }
//----------------------------------------------------------------------------
		template <class T>
        void tLista<T>::_goEnd(){
                _pi->_ind=_long-1;
                _pi->_pCur=_pUlt;
        }
//----------------------------------------------------------------------------
        template <class T>
        bool tLista<T>::_buscaPos(int pos){ 
            if ((pos>=0)&&(pos<_long)){            
				if (pos<= _pi->_ind)   
				{
					if (pos<_pi->_ind-pos)
					{
						_reinicia();
						while(_pi->_ind!=pos)
							_avanza();
					}
					else
					{
						while(_pi->_ind!=pos)
							_retrocede();
					}
					return true;
				}
				else   
				{
					if (_long-1-pos<pos-_pi->_ind)
					{
						_goEnd();
						while(_pi->_ind!=pos)
							_retrocede();
					}
					else
					{
						while(_pi->_ind!=pos)
							_avanza();
					}
					return true;
				}                
			}
			return false;
        }

//----------------------------------------------------------------------------
        template <class T>
        bool tLista<T>::_add(T info){
			tNodo* aux;                
			aux=new tNodo;
			aux->_info=info;
			//copia(aux->_info,info);

			if (_long==0)
			{
				_pCab=aux;
                aux->_sig=NULL;
				aux->_ant=NULL;
				_pUlt= aux;
                _pi = new tPuntoInteres();
                _pi->_ind=0;
                _pi->_pCur=_pCab;
				_long++;
			}
			else
			{
				_goEnd();
				aux->_sig=NULL;
				_pi->_pCur->_sig=aux;
				aux->_ant=_pi->_pCur;	
				_pUlt=aux;
				_long++;
				_avanza();
			}
			
			
        return true;
            
        }
//----------------------------------------------------------------------------
        template <class T>
		bool tLista<T>::_remove(T info)
		{
			_reinicia();
			while (_pi->_ind<_long)
			{
				if (_pi->_pCur->_info==info)
				{
					_remove(_pi->_ind);
					return true;
				}
				_avanza();				
			}
			return false;
		}


		template <class T>
        bool tLista<T>::_remove(int pos) {    
			if (_long==1)
			{
				delete _pi->_pCur;
				_long=0;
				_pCab=NULL;          
				_pUlt=NULL;          
				_pi = NULL;
			}
			else
			{
				_buscaPos(pos);
				tNodo* aux;				
				aux=_pi->_pCur;		

				if (pos==0)
				{		
					_pi->_pCur = _pi->_pCur->_sig;			
					_pCab = _pCab->_sig;
					_pCab->_ant=NULL;
					
				}
				else if (pos==_long-1)
				{  
					_retrocede();	
					_pUlt = _pUlt->_ant;	
					_pUlt->_sig = NULL;	
				}
				else
				{		
					_retrocede();					
					aux->_ant->_sig = aux->_sig;
					aux->_sig->_ant = aux->_ant;
				}
				delete aux;
				_long--;
				return true;
			}
			return false;
			
        }
//----------------------------------------------------------------------------
        template <class T>
        bool tLista<T>::_get(int num,T& info){
			if (_buscaPos(num)) 
			{
				info=_pi->_pCur->_info;
				return true;
			}
			return false;
        }
		 template <class T>

        bool tLista<T>::_getPointer(int num,T*& info){
			if (_buscaPos(num)) 
			{
				assert(num<_long);
				info=&_pi->_pCur->_info;
				return true;
			}
			return false;
        }
#endif