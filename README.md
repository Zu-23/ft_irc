# ft_irc

A C++98 IRC server developed for the 42 curriculum, with an accompanying bot. The server manages client connections, registration, channels, and text messaging over TCP.

## Features

- Password-based registration with `PASS`, `NICK`, and `USER`.
- Channel commands including `JOIN`, `PART`, `TOPIC`, `MODE`, `INVITE`, and `KICK`.
- Direct and channel messaging through `PRIVMSG` and `NOTICE`.
- `NAMES`, `MOTD`, and `QUIT` handlers.
- A separate bot under [bot](bot).

Command implementations are in [srcs/command/commands](srcs/command/commands). This is an educational server; the listed handlers do not imply full IRC specification compliance or TLS support.

## Requirements and build

Requires **Linux**, Make, and a C++ compiler available as `c++`. The server uses Linux `epoll` in addition to POSIX sockets; it does not build unchanged on macOS. The current build uses C++98 and AddressSanitizer for both compilation and linking, so the compiler's sanitizer runtime must be available.

```sh
make
./ircserv 6667 localpass
```

Run from the repository root so the server's [.MOTD](.MOTD) file is available. The command-line interface is:

```text
./ircserv <port> <password>
```

## Connect

Use an IRC client configured for host `127.0.0.1`, port `6667`, server password `localpass`, and a nickname. For a manual local session with OpenBSD netcat, use `nc -C 127.0.0.1 6667`. Its `-C` option sends the CRLF line endings required by this server. Enter these protocol lines:

```text
PASS localpass
NICK learner
USER learner 0 * :42 learner
JOIN #42
PRIVMSG #42 :Hello from 42
```

Register a second client with a different nickname to exchange messages.

## Bot

Build and run the bot separately while the server is running:

```sh
make -C bot
./bot/bot 6667 127.0.0.1 localpass
```

Its argument order is `<port> <host> <password>`. See [bot/srcs/bot](bot/srcs/bot) for its command behavior.

The server and bot Makefiles provide `clean`, `fclean`, and `re` targets; the server also has `debug`.

## Concepts practiced

TCP sockets, client lifecycle management, protocol parsing, command dispatch, channel permissions, C++ class design, and multi-client server state.
