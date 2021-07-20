#!/usr/bin/python
import subprocess, sys
code_dir = "code"
title = "3N1?M4 Team Reference"

def get_sections():
	sections = []
	section_name = None
	with open('contents.txt', 'r') as f:
		for line in f:
			if '#' in line: line = line[:line.find('#')]
			line = line.strip()
			if len(line) == 0: continue
			if line[0] == '[':
				section_name = line[1:-1]
				subsections = []
				if section_name is not None:
					sections.append((section_name, subsections))
			else:
				tmp = line.split('\t', 1)
				if len(tmp) == 1:
					raise ValueError('Subsection parse error: %s' % line)
				filename = tmp[0]
				subsection_name = tmp[1]
				if section_name is None:
					raise ValueError('Subsection given without section')
				subsections.append((filename, subsection_name))
	return sections

def get_style(filename):
	ext = filename.lower().split('.')[-1]
	if ext in ['c', 'cc', 'cpp', 'h']:
		return 'cpp'
	elif ext in ['java']:
		return 'java'
	elif ext in ['py']:
		return 'py'
	elif ext in ['sh']:
		return 'sh'    
	else:
		return 'txt'

# TODO: check if this is everything we need
def texify(s):
	s = s.replace('_', '\_')
	return s

def get_tex(sections):
	tex = ''
	for (section_name, subsections) in sections:
		tex += '\\section{%s}\n' % texify(section_name)
		for (filename, subsection_name) in subsections:
			tex += '\\subsection{%s}\n' % texify(subsection_name)
			tex += '\\texttt{file: %s}\n' % texify(filename)
			tex += '\\raggedbottom\\lstinputlisting[style=%s]{%s/%s}\n' % (get_style(filename), code_dir, filename)
			tex += '\\hrulefill\n'
		tex += '\n'
	return tex

def process_file(filename):
	filename = './code/' + filename
	f = open(filename)
	L = f.readlines()
	f.close()

	f = open(filename, 'w')
	for line in L: 
		for c in line:
			if c != '\t':
				f.write(c)
			else:
				f.write('    ')     

def tabs_to_spaces():
	with open('contents.txt', 'r') as f:
		for line in f:
			if '#' in line: line = line[:line.find('#')]
			line = line.strip()
			if len(line) == 0: continue
			if line[0] != '[':
				tmp = line.split('\t')
				process_file(tmp[0])


if __name__ == "__main__":
	tabs_to_spaces()
	sections = get_sections()
	
	# print sections

	# put_filename(sections);

	tex = get_tex(sections)
	with open('contents.tex', 'w') as f:
		f.write(tex)
	latexmk_options = ["latexmk", "-pdf", "notebook.tex"]
	# latexmk_options = ["latexmk", "-pdf", "-silent", "notebook.tex"]
	
	status = subprocess.call(latexmk_options)
	sys.exit(status)
