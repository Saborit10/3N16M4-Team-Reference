#! /usr/bin/python3

import os

INDEX_FILE = '/home/luis/TEAM REFERENCE/contents.txt'
SEP = '/* =========================== TEMPLATE CODE =========================== */\n'
EXTENSION = '.cpp'
CODE_FOLDER = '/home/luis/TEAM REFERENCE/code'
LINE = 31

TOPOLOGICAL_ORDER = []

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

	# print(line, template, filename)
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

def recursive_collect(template):
	dependencies = []

	with open(INDEX_FILE, 'r') as f:
		for line in f:
			dep = ''

			if '#' in line:
				id = line.find('#')
				dep = line[id+1:].strip()
				line = line[:id]
			line = line.strip()
			if len(line) == 0: continue
			if line[0] != '[':
				tmp = line.split('\t', 1)
				# print(tmp[0], template)
				if tmp[0] == template:
					for i in dep.split('\t'):
						if len(i) > 0:
							dependencies.append(i)	
					# print(template + " :: " + str(dependencies))
	# print("LINE_NUMBER: " + line)

	for d in dependencies:
		# print('REC: ' + d)
		recursive_collect(d)

	TOPOLOGICAL_ORDER.append(template)

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

	recursive_collect(template)

	TOPOLOGICAL_ORDER.reverse()

	for template in TOPOLOGICAL_ORDER:
		inyect(LINE, os.path.join(CODE_FOLDER, template), filename)
		print('Generado %s.' % template)

	print('========================================')
	