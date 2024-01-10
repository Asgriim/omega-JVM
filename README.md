# Omega-JVM

## Как
``git clone``

``cmake -B target``

``cmake --build target --target omega-jvm``

Требуется библиотека ```libzip``` для сборки.

После этого можно запустить через ./target/omega-jvm.

## Проверка 
Можно запустить файлы из директории ``java_files``.

Работоспособность остальных файлов не гарантируется.

## Пример

``./omega-jvm java_files/Aboba`` - где ``Aboba`` это скомпилированный .class файл.

``./omega-jvm -jar java_files/hello.jar``