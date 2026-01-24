# 3 Way-Verification  



# Overview 

## 3 Way-Verification is an internal tool that helps provide high security level through hash-checking, user identification, hardware-level security, advanced ACL, SACL and DACL usage and more.


# What 3WV is capable of and how it makes you experience secured.

## 3WV don't help you overstep the law regulations and laws itself. It helps you keep what's yours. Your anonymity is your responsibility, but your security might be achieved by using the right tools. 3WV helps your tools stay yours.


## 3WV helps to preserve a lot kinds of attacks to your identity and security - 

* Substitution of trusted applications
* Compromised operating system
* Code integrity violation
* Drivers integrity violation
* Digital signature violation
* Memory integrity violation
* Compromised network
* Key-loggers detection and prevention
* Screen-recorders detection and prevention
* Audio-recording detection and prevention


# How does this work

## By default every compilation of program that relies on 3WV use -OBSESSION or -ENABLE_3WV compilation flag so that 3WV will be compiled and used by the application. Despite overhead of the 3WV usage is almost nothing you may want your progam to work faster or just disable this feature. For these purpose use -WYSIWYG or -DISABLE_3WV.








# Build

## If your program declares usage of 3WV its already know how to compile it. But there's the few features you may want to change  

### Macros

* -OBSESSION - this macro is idiom means 'a little bit too much security'. Although it is actually not. This macro enable not only 3WV but every security application and tool available.
* -WYSIWYG - this macro is idiom means 'what you see is what you got'. This macro disables all additional security features.
* -ENABLE_3WV - this macro enable 3WV tool. Have higher priority than -WYSIWYG .
* -DISABLE_3WV - this macro disable 3WV tool. Have higher priority than -OBSESSION .
* -3WV_TRANSPARENT - this macro enable hiding features. 3WV will hide from system as well as from the user and will be accessible only by special methods known to the application only.
* -3WV_RESTRICT - this macro enable deleting/accessing/updating/changing accessiable by the application only. This means only program registered with 3WV will be able to interact with 3WV by the all available methods(d/a/u/c) described above.
