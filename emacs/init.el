;; remove default decorations
(tool-bar-mode -1)
(toggle-scroll-bar -1)
(menu-bar-mode -1)

;; bootstrap for Straight package manager
(defvar bootstrap-version)
(let ((bootstrap-file
       (expand-file-name "straight/repos/straight.el/bootstrap.el" user-emacs-directory))
      (bootstrap-version 5))
  (unless (file-exists-p bootstrap-file)
    (with-current-buffer
        (url-retrieve-synchronously
         "https://raw.githubusercontent.com/raxod502/straight.el/develop/install.el"
         'silent 'inhibit-cookies)
      (goto-char (point-max))
      (eval-print-last-sexp)))
  (load bootstrap-file nil 'nomessage))

;; evil-mode for vi(m) like behavior
(straight-use-package 'evil)
(evil-mode 1)

;; flycheck
(straight-use-package 'flycheck)
(global-flycheck-mode 1)

;; use semantic mode by default
(semantic-mode 1)
(global-semantic-idle-scheduler-mode 1)

;; helm package for finding files
(straight-use-package 'helm)
(helm-mode 1)
(setq completion-styles '(flex))

;; clang-format on f9 from github.com/llvm-mirror/clang/blob/master/tools/clang-format/clang-format.el
;; required .clang-format in the .emacs.d dir
(load "~/.emacs.d/clang-format.el")
(setq clang-format-style "file")
(global-set-key [f9] 'clang-format-region)

;; setting font
(set-frame-font "Consolas 14" nil t)

;; web-mode for JS
(straight-use-package 'web-mode)
(setq web-mode-script-padding 2)
(add-to-list 'auto-mode-alist '("\\.html\\'" . web-mode))
(add-to-list 'auto-mode-alist '("\\.js\\'" . web-mode))
(add-to-list 'auto-mode-alist '("\\.json\\'" . web-mode))
(add-to-list 'auto-mode-alist '("\\.css\\'" . web-mode))

;; atom-one-dark theme from github.com/jonathanchu/atom-one-dark-theme
(add-to-list 'custom-theme-load-path "~/.emacs.d/atom-one-dark-theme")
(load-theme 'atom-one-dark t)

;; invoke helm-find-files by pressing f8
(global-set-key (kbd "<f8>") (lambda () (interactive) (helm-find-files -1)))

(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(display-line-numbers t)
 '(indent-tabs-mode nil)
 '(inhibit-startup-screen t)
 '(ring-bell-function 'ignore)
 '(standard-indent 2)
 '(visible-bell nil))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )
