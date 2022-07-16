# Geolocation_Cplusplus main file in Geolocation_Cplusplus/Geolocation_Cplusplus.cpp
Geolocalizador de IP feito em c++ para NAP 2 da disciplina Técnicas de programação II do curso SISTEMAS DE INFORMAÇÃO - UFRA
O sistema foi feito usando as dependências POCO para requisições HTTP e/ou HTTPS para a api de consulta de geolocalização que retornará os dados baseado no endereço ipv4 do computador. 
O sistema captura o endereço automáticamente mas caso o usuário queira também pode fazer a consulta de um outro ip digitando o mesmo manualmente, em seguida os dados retornados da api em formato JSON e convertidos em string serão salvos em um arquivo no computador como um histórico de buscas, o sistema também permite que o usuário faça um CRUD desses dados no arquivo ou até mesmo removê-lo. 
Também foram usadas bibliotecas de recursos padrões do windows(wininet, windows.h...), bem como 
as bibliotecas padrões do c++ para a manipulação de arquivos como <ifstream.h> e <fstream.h>, todas as dependências trabalham em conjunto para fornecer a execução 
estável do sistema.


Required: instalação do Visual Studio com o recurso desenvolvimento c++ para desktop.
