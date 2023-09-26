let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/Desktop/LOCAL/minishell
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +20 ~/Desktop/LOCAL/minishell/srcs/exec/ms_builtins_part_2.c
badd +57 ~/Desktop/LOCAL/minishell/srcs/exec/ms_builtins_part_1.c
badd +26 ~/Desktop/LOCAL/minishell/srcs/exec/ms_exec.c
badd +48 ~/Desktop/LOCAL/minishell/minishell.h
badd +15 ~/Desktop/LOCAL/minishell/srcs/tokenizer/ms_pathed_command.c
badd +0 ~/Desktop/LOCAL/minishell/srcs/utils/ms_error_codes.c
badd +0 ~/Desktop/LOCAL/minishell/srcs/parsing/ms_env_utils.c
argglobal
%argdel
edit ~/Desktop/LOCAL/minishell/srcs/parsing/ms_env_utils.c
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
wincmd _ | wincmd |
vsplit
2wincmd h
wincmd _ | wincmd |
split
1wincmd k
wincmd w
wincmd w
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
wincmd =
argglobal
balt ~/Desktop/LOCAL/minishell/srcs/exec/ms_exec.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 60 - ((10 * winheight(0) + 17) / 34)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 60
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("~/Desktop/LOCAL/minishell/srcs/exec/ms_exec.c", ":p")) | buffer ~/Desktop/LOCAL/minishell/srcs/exec/ms_exec.c | else | edit ~/Desktop/LOCAL/minishell/srcs/exec/ms_exec.c | endif
if &buftype ==# 'terminal'
  silent file ~/Desktop/LOCAL/minishell/srcs/exec/ms_exec.c
endif
balt ~/Desktop/LOCAL/minishell/srcs/parsing/ms_env_utils.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 22 - ((7 * winheight(0) + 16) / 33)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 22
normal! 047|
wincmd w
argglobal
if bufexists(fnamemodify("~/Desktop/LOCAL/minishell/srcs/exec/ms_builtins_part_1.c", ":p")) | buffer ~/Desktop/LOCAL/minishell/srcs/exec/ms_builtins_part_1.c | else | edit ~/Desktop/LOCAL/minishell/srcs/exec/ms_builtins_part_1.c | endif
if &buftype ==# 'terminal'
  silent file ~/Desktop/LOCAL/minishell/srcs/exec/ms_builtins_part_1.c
endif
balt ~/Desktop/LOCAL/minishell/srcs/tokenizer/ms_pathed_command.c
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 57 - ((40 * winheight(0) + 34) / 68)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 57
normal! 037|
wincmd w
argglobal
if bufexists(fnamemodify("~/Desktop/LOCAL/minishell/srcs/utils/ms_error_codes.c", ":p")) | buffer ~/Desktop/LOCAL/minishell/srcs/utils/ms_error_codes.c | else | edit ~/Desktop/LOCAL/minishell/srcs/utils/ms_error_codes.c | endif
if &buftype ==# 'terminal'
  silent file ~/Desktop/LOCAL/minishell/srcs/utils/ms_error_codes.c
endif
balt ~/Desktop/LOCAL/minishell/minishell.h
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 46 - ((45 * winheight(0) + 34) / 68)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 46
normal! 0
wincmd w
wincmd =
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
let g:this_session = v:this_session
let g:this_obsession = v:this_session
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
