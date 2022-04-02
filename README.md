# KIV-PSI-2HW
Second HW assigned in KIV/PSI
1) Obsah repozitáře

Repozitář obsahuje ve složce "CLion projekt" celý projekt, který byl vytvořen ve vývojovém prostředí JetBrains CLion. V rootu repozitáře se nacházejí zdrojové kódy programu a makefile, který je možno použít pro sestavení programu.

2) Princip funkce programu - BSD socket

Aplikace je psána v jazyce C a využívá klasické rozhraní BSD socketů. V programu jsou tedy volány funkce typické pro BSD sockety, jejichž princip funkce je popsán v následujících podkapitolách. Detailní popis je možno nalézt například na následující web. stránce: https://www.geeksforgeeks.org/socket-programming-cc/

2.a) socket(domain, type, protocol)

Vytvoří socket pro otevření spojení, handler.

2.b) int bind(int sockfd, const struct sockaddr \*addr, socklen_t addrlen)

Naváže socket k určité adrese a portu. Aplikace umožňuje zvolit port, na kterém bude naslouchat. Http protokol používá port 80, pro otestování serveru prohlížečem je tedy výhodné volit tento port.

2.c) int listen(int sockfd, int backlog)

Zahájí naslouchání na socketu (sockfd) a čeká na připojení klientů k serveru. Backlog udává maximální počet klientů, kteří se mohou připojit. Pokud je dosaženo maximálního počtu klientů, obdrží další klient kód ECONNREFUSED.

2.d) accept(int sockfd, struct sockaddr \*addr, socklen_t \*addrlen)

Přijme klienta čekajícího na spojení se serverem. Pokud jich je ve frontě více, má přednost klient, který přišel dříve. Sockfd je socket serveru a addr specifikuje adresu klienta.

3) Princip funkce programu - popis workflow

Program po spuštění zahájí naslouchání na uživatelem specifikovaném portu, který je předán jako parametr programu. Při připojení klienta je pro jeho obsluhu vytvořeno nové vlákno, ve kterém probíhá vyřizování požadavků ze strany klienta (prohlížeče).

Obsluha je řešena pomocí funkce void * client_handler_thread(void \*arg), ve které dojde k přečtení zprávy od klienta. Zpráva je přečtena pouze za předpokladu, že má nenulovou délku a zároveň nepřekračuje délku určenou konstantou SERVER_MES_BUF_SIZE.

Po přečtení zprávy je nejprve zjištěno, zda zpráva od klienta obsahuje požadavek typu GET. Pokud je GET přítomen, zkontroluje funkce, zda požadavky v rámci GET odpovídají požadovanému formátu. Pokud ano, je sestavena webová stránka odpovídající požadavkům uživatele. Pokud uživatelská zpráva neodpovídá očekávanému formátu, vrátí se uživateli stránka error page.

4) Konstanty umožňující změnu chování programu

Změna níže uvedených konstant, jež se nachází ve zdrojovém kódu serveru, povede ke změně chování programu odpovídajícím způsobem.

4.a) Změna obsahu web. stránky - hello

V hlavičkovém souboru "logic_response.h" se nachází konstanta "SERVER_RESP_CMD_1", která obsahuje odpověď na požadavek typu "user_get=hello". Změnou je možno zajistit vykreslení alternativní web. stránky na uvedený požadavek.

4.b) Změna obsahu web. stránky - creator

Analogicky - v souboru "logic_response.h" konstanta "SERVER_RESP_CMD_2" popisuje odpověď na požadavek "user_get=creator".

4.c) Změna obsahu web. stránky - github

Analogicky - v souboru "logic_response.h" konstanta "SERVER_RESP_CMD_3" popisuje odpověď na požadavek "user_get=github".

4.d) Změna obsahu web. stránky - error

Soubor "logic_response.h" v konstantě "SERVER_RESP_ERR" obsahuje odpověď, která je uživateli vypsána, pokud není rozpoznán žádný validní požadavek.

4.e) Změna nadpisu stránky, title

V souboru "logic_response.h", kontanta "SERVER_RESP_START" je možno změnit nadpis generované webové stránky.

4.f) Změna maximálního počtu klientů

Soubor "logic_server.h" obsahuje konstantu "SERVER_MAX_CLIENT_NUM", která definuje maximální počet spojení.

4.g) Změna velikosti bufferu pro zprávy od klientů

Soubor "logic_server.h" obsahuje konstantu "SERVER_MES_BUF_SIZE", jež definuje velikost bufferu pro zprávy přijímané od klienta.

4.h) Změna debug zprávy vypisovaných serverem

Soubor "logic_server.h" obsahuje veškeré zprávy, jež program vypisuje do konzole. Zprávy lze tedy snadno změnit a definovat si vlastní.

5) Spuštění aplikace, návod k použití

5.a) Spuštění serveru

Aplikace byla napsána v jazyce C. Uživatelsky přívětivé spuštění je možné díky přibalenému makefile. Pro spuštění tedy stačí v rootu repozitáře vykonat příkaz "make" a po kompilaci by měl vzniknout soubor "tcpserver". Následné spuštění provedeme příkazem "./tcpserver CISLO_PORTU", kde CISLO_PORTU je port, na kterém bude server naslouchat. Pro otestování pomocí prohlížeče doporučuji port 80, jež je běžně využíván protokolem http.

Vzorové spuštění tedy může vypadat například takto "./tcpserver 80". Uvedený příkaz spustí server na portu 80.

Program je možno spustit i z prostředí CLion. Pro využití této metody importujte projekt, který se nachází ve složce "CLion projekt".

5.b) Otestování, formát požadavků

Po startu serveru ve webovém prohlížeči zadejte IP stroje, na kterém běží server, následovanou "/?" a některými z validních příkazů. Za validní příkazy jsou považovány následující sekvence znaků:
- user_get=hello
- user_get=creator
- user_get=github

Příkazy je možno řetězit pomocí znaku "?". Níže jsou tedy příklady několika validních adres (server běží na portu 1456):
- http://localhost:1456/?user_get=hello
- http://localhost:1456/?user_get=hello?user_get=creator
- http://localhost:1456/?user_get=hello?user_get=creator?user_get=github

Pro ilustraci přikládám snímek web. stránky, jež se zobrazí při přejití na poslední z uvedených webových stránek.
![scr](https://user-images.githubusercontent.com/44243474/161376976-f0ebeac1-999e-4ef0-abbb-ee2cf7e34833.png)

Pokud nebude rozpoznán žádný validní příkaz, vrátí se uživateli stránka s chybou, viz následující obrázek.
![scr2](https://user-images.githubusercontent.com/44243474/161377095-6f413ec2-ae4c-40f6-9e1d-4ad17567a5a3.png)
