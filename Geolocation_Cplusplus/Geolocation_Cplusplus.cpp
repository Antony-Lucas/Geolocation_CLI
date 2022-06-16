#include <Poco/URI.h>
#include <Poco/Net/HTTPClientSession.h> 
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/File.h>
#include "Poco/StreamCopier.h"
#include <fileapi.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <direct.h>
#include <windows.h>
#include <winInet.h>
#include <locale.h>
#include <filesystem>

#pragma comment(lib,"Wininet.lib")

//REFERÊNCIAS NO FINAL DO CÓDIGO
//namespaces reservados das dependencias.
using namespace std;
using namespace Poco;
using namespace Poco::Net;
using namespace std::experimental::filesystem::v1;
namespace fs = std::filesystem;

//structs
typedef struct {
    short unsigned Option;
    short unsigned FileOption;
}Switchable;

typedef struct {
    const char* path;
    unsigned int end;
    size_t alloc;
    string content;
}Create;

typedef struct {
    char buff[4096];
    DWORD read;
    LPCWSTR ip;
    LPCWSTR uri;
}IpReceiver;

typedef struct {
    ostringstream oss;
    string respounse;
    string responsed;
}GetLoc;

typedef struct {
    int openf;
    string updater;
    string content;
}UpdateArch;

//publicos
Create BuildFile;
//funcoes
void Menu();
void CreateDef();
void OpenFile();
void UpdateFile();
void EraseFile();
void dell();
string GetLocation(string url);
string ipAdr();

int main(void)
{
    setlocale(LC_ALL, "Portuguese");
    system("cls");
    Menu();
    return 0;
}

void Menu() {
    Switchable MainMenu;
    ifstream ifs("C:\\suas_informacoes\\1MyInfo_.txt");
    cout << "\n\t\x1B[33mGeolocalizador de IP\033[0m\n\n";
    cout << "\tSeu endereco de IP: ";
    cout << "\x1B[32m" + ipAdr() + "\033[0m\n\n\n";
    cout << "\t\tMenu\n\n";
    cout << "[1] Gerar arquivo de informacoes\n";
    cout << "[2] Alterar IP de consulta\n";
    cout << "[3] Deletar dados\n";
    cout << "[4] Sair do sistema\n";

    if (ifs) {
        cout << "[0] Abrir arquivo de informacoes\n";
        cout << "\n\n====================================================================";
        cout << "\nArquivo presente em:";
        cout << "\nC://suas_informacoes/1MyInfo_.txt\n";
        cout << "====================================================================\n\n";
    }
    else {
        cout << "\n\n====================================================================";
        cout << "\nArquivos:";
        cout << "\nVoce ainda nao gerou nenhuma informacao\n";
        cout << "====================================================================\n\n";
    }

    cout << "Escolha uma acao: ";
    cin >> MainMenu.Option;

    switch (MainMenu.Option) {
    case 1:
        system("cls");
        CreateDef();
        break;
    case 2:
        system("cls");
        UpdateFile();
        break;
    case 3:
        system("cls");
        EraseFile();
        break;
    case 4:
        exit(EXIT_SUCCESS);
        break;
    case 0:
        system("cls");
        OpenFile();
        break;
    default: system("cls"); Menu();
    }
}

void CreateDef() {
    Switchable FileMenu;
    fstream file;
    BuildFile.content = "{\n\t\tHistórico de buscas\n\n: " + GetLocation(ipAdr()) + "\n}";
    BuildFile.alloc = 0;
    BuildFile.path = "C:\\suas_informacoes\\";
    _mkdir(BuildFile.path);

    BuildFile.alloc++;
    //std::ios_base::out é equivalente a "w" em fopen
    file.open(BuildFile.path + to_string(BuildFile.alloc) + "MyInfo_.txt", ios_base::out);
    file << BuildFile.content;
    file.close();
    cout << "Arquivo criado em: C://suas_informacoes/1MyInfo_.txt" + to_string(BuildFile.alloc) + "\r\n";
    Sleep(100);

    std::cout << "[1] Abrir arquivo\n";
    std::cout << "[0] Voltar ao menu\n";
    std::cin >> FileMenu.FileOption;

    switch (FileMenu.FileOption) {
    case 1:
        OpenFile();
        break;
    case 0:
        system("cls");
        Menu();
        break;
    default:
        std::cout << "Opcao invalida, voltando ao menu...";
        Sleep(2500);
        system("cls");
        Menu();
    }
}

void UpdateFile() {
    Switchable UpdateMenu;
    UpdateArch up;
    fstream file;
    ifstream ifs("C:\\suas_informacoes\\1MyInfo_.txt");

    if (ifs) {
        cout << "\n[1] Informar um novo endereco de IP\n";
        cout << "[0] Voltar ao menu\n";
        cin >> UpdateMenu.Option;

        switch (UpdateMenu.Option) {
        case 1:
            cout << "\n\x1B[32mInforme um novo endereco de IP(ipv4)\033[0m: ";
            cin >> up.updater;

            cout << "\n\n\t\tResultado da busca: " + up.updater << "\n\n";
            cout << GetLocation(up.updater);

            cout << "\n\n[2] confirmar atualizacao de dados";
            cout << "\n[1] abrir arquivo";
            cout << "\n[0] voltar ao menu\n";
            cin >> UpdateMenu.FileOption;

            switch (UpdateMenu.FileOption) {
            case 2:
                up.content = "\n{\n: " + GetLocation(up.updater) + "\n}";
                //std::ios_base::app = append e std::ios_base::app = input
                file.open("C:\\suas_informacoes\\1MyInfo_.txt", ios_base::app | ios_base::in);
                file << up.content;
                file.close();

                cout << "Historico de busca atualizado com sucesso!\n deseja visualizar o arquivo?\n";
                cout << "[1] sim [0] nao\n";
                cin >> up.openf;
                switch (up.openf) {
                case 1:
                    OpenFile();
                    break;
                case 0:
                    system("cls");
                    UpdateFile();
                    break;
                default: system("cls"); UpdateFile();
                }
                break;
            case 1:
                system("cls");
                OpenFile();
                break;
            case 0:
                system("cls");
                Menu();
                break;
            default: system("cls"); UpdateFile();
            }
            break;
        case 0:
            system("cls");
            Menu();
            break;
        default: system("cls"); UpdateFile();
        }
    }
    else {
        cout << "\n\x1B[33mNao existem dados no sistema para atualizar, primeiro crie um arquivo para usar essa funcao.\033[0m\n";
        cout << "[0] voltar ao menu\n";
        cin >> UpdateMenu.Option;

        switch (UpdateMenu.Option) {
        case 0:
            system("cls");
            Menu();
            break;
        default: UpdateFile();
        }
    }
}

void EraseFile() {
    Switchable EraseMenu;
    error_code err;
    fstream file;
    ifstream ifs("C:\\suas_informacoes\\1MyInfo_.txt");

    if (ifs) {
        cout << "\n\n[2] Deletar informacoes";
        cout << "\n\x1B[31m[1] Excluir diretorio do arquivo\033[0m";
        cout << "\n[0] voltar ao menu\n";
        cin >> EraseMenu.Option;

        switch (EraseMenu.Option)
        {
        case 2:
            file.open("C:\\suas_informacoes\\1MyInfo_.txt", ios_base::out | ios_base::trunc);
            file.close();

            cout << "\n\n\x1B[31mConteudo do arquivo 1MyInfo_.txt apagado com sucesso!\033[0m\n";
            cout << "[1] visualizar arquivo\n";
            cout << "[0] voltar ao menu\n";
            cin >> EraseMenu.FileOption;

            switch (EraseMenu.FileOption) {
            case 1:
                system("cls");
                OpenFile();
                break;
            case 0:
                system("cls");
                Menu();
                break;
            default: system("cls"); EraseFile();
            }
            break;
        case 1:
            _fcloseall();
            fs::remove_all("C:\\suas_informacoes", err);
            cout << err.message() << "Voltando ao menu...";
            Sleep(3500);
            system("cls");
            Menu();
            break;
        case 0:
            system("cls");
            Menu();
            break;
        default: system("cls"); EraseFile();
        }
    }
    else {
        cout << "\n\x1B[33mNao existem dados no sistema para Excluir, primeiro crie um arquivo para usar essa funcao.\033[0m\n";
        cout << "[0] voltar ao menu\n";
        cin >> EraseMenu.Option;

        switch (EraseMenu.Option) {
        case 0:
            system("cls");
            Menu();
            break;
        default: UpdateFile();
        }
    }
}

string GetLocation(string url) {
    GetLoc location;

    URI uri("http://api.ipapi.com/api/" + url + "?access_key=6befefe50975dede4dc6da6dc6467327");
    string path(uri.getPathAndQuery());
    if (path.empty()) path = "/";

    HTTPClientSession session(uri.getHost(), uri.getPort());

    session.setKeepAlive(true);
    HTTPRequest request(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
    request.setContentType("application/json");
    request.add("User-Agent", "Mozilla/5.0");
    session.sendRequest(request);
    HTTPResponse response;
    istream& page = session.receiveResponse(response);

    location.oss;
    location.respounse;
    StreamCopier::copyStream(page, location.oss);
    location.responsed = location.oss.str();

    return location.responsed;
}

string ipAdr() {
    IpReceiver retrivier;

    retrivier.ip = L"IP retrivier";
    retrivier.uri = L"http://myexternalip.com/raw";

    HINTERNET net = InternetOpen(retrivier.ip, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    HINTERNET con = InternetOpenUrl(net, retrivier.uri, NULL, 0, INTERNET_FLAG_RELOAD, 0);

    InternetReadFile(con, retrivier.buff, sizeof(retrivier.buff) / sizeof(retrivier.buff[0]), &retrivier.read);
    InternetCloseHandle(net);

    return string(retrivier.buff, retrivier.read);
}

void OpenFile() {
    system("C:\\suas_informacoes\\1MyInfo_.txt");
    system("cls");
    Menu();
}

//https://cplusplus.com/reference/fstream/ofstream/open/
//https://cplusplus.com/reference/ios/ios_base/openmode/
//https://stackoverflow.com/questions/12253183/stdios-baseate-and-stdios-basetrunc
//https://docs.pocoproject.org/current/Poco.Net.HTTPRequest.html
//https://www.codeproject.com/Articles/252566/Learning-Poco-GET-with-HTTP
//https://juejin.cn/post/6963596454606667790 开源项目推荐：POCO C++ Libraries大全，含MFC的编译及使用 
//https://cplusplus.com/doc/tutorial/files/
//https://docs.microsoft.com/pt-br/cpp/mfc/wininet-basics?view=msvc-170
//https://stackoverflow.com/questions/37666668/wininet-and-internetopen
//https://docs.microsoft.com/en-us/windows/win32/winhttp/hinternet-handles-in-winhttp
//https://stackoverflow.com/questions/47585436/how-to-get-url-from-hinternet-handle
//https://en.cppreference.com/w/cpp/filesystem
//https://docs.microsoft.com/pt-br/cpp/standard-library/filesystem?view=msvc-170