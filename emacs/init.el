;; evil-mode for vi(m) like behavior
(add-to-list 'load-path "~/.emacs.d/evil")
(require 'evil)
(evil-mode 1)

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

;; remove decorations
(tool-bar-mode -1)
(menu-bar-mode -1)

;; helm package for finding files
(straight-use-package 'helm)
(helm-mode 1)
(setq completion-styles '(flex))

;; setting font
(set-frame-font "Consolas 14" nil t)

;; atom-one-dark theme
(add-to-list 'custom-theme-load-path "~/.emacs.d/atom-one-dark-theme")
(load-theme 'atom-one-dark t)


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
