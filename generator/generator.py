
import os

INDEX_FILE = '../contents.txt'
SEP = '/* =========================== TEMPLATE CODE =========================== */\n'
EXTENSION = '.cpp'
CODE_FOLDER = '../code'
LINE = 31

def get_index():
	codes = []
	
	with open(INDEX_FILE, 'r') as f:
		for line in f:
			if '#' in line: line = line[:line.find('#')]
			line = line.strip()
			if len(line) == 0: continue
			if line[0] != '[':
				tmp = line.split('\t', 1)
				if len(tmp) != 2:
					raise ValueError('Subsection parse error: %s' % line)
				codes.append((tmp[0], tmp[1]))	
	return codes

def filter(keyword):
	keyword = keyword.lower()
	lista = []

	for (path, title) in index:
		if keyword in title.lower() or keyword in path.lower():
			lista.append((path, title))
	return lista

def select(lista, msg):
	print('\n========================================')
	print(msg)
	print("[0] Abortar")
	for i in range(len(lista)):
		print("[%d] %s" % (i+1, lista[i][1]))
	print('========================================')
	id = input('Introduce un indice: ')

	try:
		id = int(id)
		if id < 0 or id > len(lista):
			raise ValueError('Indice fuera de rango')
	except:
		print("Indice incorrecto")

	if id == 0:
		return None
	else:
		return lista[id-1]


def inyect(line, template, filename):
	f = open(filename, 'r')
	code = f.readlines()
	f.close()

	while len(code[line].strip()) > 0:
		line += 1

	f = open(template, 'r')
	temp = f.readlines()
	f.close()

	f = open(filename, 'w')
	
	for x in code[:line]:
		f.write(x)
	f.write('\n')
	f.write(SEP)
	f.write('\n')
	
	for x in temp:
		f.write(x)
	f.write('\n')
	f.write(SEP)
	f.write('\n')
	
	for i in range(line+1, len(code)):
		f.write(code[i])
	
	f.close()


if __name__ == '__main__':
	index = get_index()

	# files = os.listdir('.')
	# print(files)

	files = [(None, x) for x in os.listdir('.') if x.endswith(EXTENSION)]

	filename = select(files, "Seleccione el archivo a modificar:")

	if filename == None:
		exit(0)
	filename = filename[1]

	keyword = input("Search: ")

	template = select(filter(keyword), "Seleccione la plantilla a generar:")

	if template == None:
		exit(0)
	template = template[0]

	inyect(LINE, os.path.join(CODE_FOLDER, template), filename)

	print('========================================')
	print('Codigo de la plantilla generado correctamente.')