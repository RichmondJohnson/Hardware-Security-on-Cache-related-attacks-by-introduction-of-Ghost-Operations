; ModuleID = 'InputFiles/_TP4_circles/circles.c'
target datalayout = "e-m:e-p:32:32-f64:32:64-f80:32-n8:16:32-S128"
target triple = "i686-pc-linux-gnu"

@.str = private unnamed_addr constant [11 x i8] c"Enter r : \00", align 1
@.str.1 = private unnamed_addr constant [3 x i8] c"%f\00", align 1
@.str.2 = private unnamed_addr constant [23 x i8] c"Circumference is : %f\0A\00", align 1
@.str.3 = private unnamed_addr constant [14 x i8] c"Area is : %f\0A\00", align 1

; Function Attrs: nounwind
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %circumference = alloca float, align 4
  %areas = alloca float, align 4
  %r = alloca float, align 4
  store i32 0, i32* %1, align 4
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str, i32 0, i32 0))
  %3 = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.1, i32 0, i32 0), float* %r)
  %4 = load float, float* %r, align 4
  %5 = call float @cir(float %4)
  store float %5, float* %circumference, align 4
  %6 = load float, float* %r, align 4
  %7 = call float @area(float %6)
  store float %7, float* %areas, align 4
  %8 = load float, float* %circumference, align 4
  %9 = fpext float %8 to double
  %10 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.2, i32 0, i32 0), double %9)
  %11 = load float, float* %areas, align 4
  %12 = fpext float %11 to double
  %13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.3, i32 0, i32 0), double %12)
  %14 = load float, float* %areas, align 4
  %15 = fptosi float %14 to i32
  ret i32 %15
}

declare i32 @printf(i8*, ...) #1

declare i32 @__isoc99_scanf(i8*, ...) #1

; Function Attrs: nounwind
define float @cir(float %r) #0 {
  %1 = alloca float, align 4
  %c = alloca float, align 4
  store float %r, float* %1, align 4
  %2 = load float, float* %1, align 4
  %3 = fpext float %2 to double
  %4 = fmul double 6.280000e+00, %3
  %5 = fptrunc double %4 to float
  store float %5, float* %c, align 4
  %6 = load float, float* %c, align 4
  ret float %6
}

; Function Attrs: nounwind
define float @area(float %r) #0 {
  %1 = alloca float, align 4
  %a = alloca float, align 4
  %ci = alloca float, align 4
  store float %r, float* %1, align 4
  %2 = load float, float* %1, align 4
  %3 = call float @cir(float %2)
  store float %3, float* %ci, align 4
  %4 = load float, float* %ci, align 4
  %5 = load float, float* %ci, align 4
  %6 = fmul float %4, %5
  %7 = fpext float %6 to double
  %8 = fdiv double %7, 1.256000e+01
  %9 = fptrunc double %8 to float
  store float %9, float* %a, align 4
  %10 = load float, float* %a, align 4
  ret float %10
}

attributes #0 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="pentium4" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="pentium4" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.8.1 (tags/RELEASE_381/final)"}
