Сборка модуля - make

Загрузка модуля - make load
	Для корректной загрузки модуля необходимо наличие файла ./config.mk.
	Файл config.mk можно задать вручную или при помощи config-tool.
	
	Формат config.mk:
		file_name="/absolute_path"
		print_every_n_sec=5
		
	file_name - целевой файл для печати
	print_every_n_sec - интервал между печатью в секундах
	
Выгрузка модуля - make unload
