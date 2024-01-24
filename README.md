# Omega-JVM

## Как
``git clone``

``cmake -B target``

``cmake --build target --target omega-jvm``

Требуется библиотека [libzip](https://github.com/nih-at/libzip) для сборки.

После этого можно запустить через ./target/omega-jvm.

## Проверка 
Можно запустить файлы из директории ``java_files``.

Работоспособность остальных файлов не гарантируется.

## Что умеет 
``java/lang/*`` классы не поддерживаются, но реализован [P/invoke](https://en.wikipedia.org/wiki/Platform_Invocation_Services) для вызова нативных функций из dll линуха. [Пример](https://github.com/Asgriim/omega-JVM/blob/main/java_files/jar_example/src/main/java/org/example/platform/Console.java).
[Пример2](https://github.com/Asgriim/omega-JVM/blob/main/java_files/jar_example/src/main/java/org/example/Main.java).

Вроде ещё есть ветвления, объекты и циклы, но уверенности нет.

## Пример

``./omega-jvm java_files/Aboba`` - где ``Aboba`` это скомпилированный .class файл.

``./omega-jvm -jar java_files/hello.jar``