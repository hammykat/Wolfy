module Raycasting

    use iso_c_binding
    implicit none


contains


    subroutine GetRayData(RayX, RayY, Angle, &
                      WallX1, WallY1, WallX2, WallY2, &
                      RayCount, WallCount, &
                      OutputX, OutputY, OutputDist) bind(C)

        use iso_c_binding
        implicit none

        real(c_float), intent(in) :: RayX, RayY

        integer(c_int32_t), value, intent(in) :: RayCount
        integer(c_int32_t), value, intent(in) :: WallCount

        real(c_float), intent(in) :: Angle(0:RayCount-1)

        real(c_float), intent(in) :: WallX1(0:WallCount-1)
        real(c_float), intent(in) :: WallY1(0:WallCount-1)
        real(c_float), intent(in) :: WallX2(0:WallCount-1)
        real(c_float), intent(in) :: WallY2(0:WallCount-1)

        real(c_float), intent(out) :: OutputX(0:RayCount-1)
        real(c_float), intent(out) :: OutputY(0:RayCount-1)
        real(c_float), intent(out) :: OutputDist(0:RayCount-1)


        ! Local vars
        real(c_float) :: RayDirX, RayDirY
        real(c_float) :: WallDirX, WallDirY

        real(c_float) :: Denom
        real(c_float) :: DeltaX, DeltaY

        real(c_float) :: T, U
        real(c_float) :: ClosestDistance
        real(c_float) :: HitX, HitY

        integer(c_int32_t) :: i
        integer(c_int32_t) :: j


        ! Every ray
        do i = 0, RayCount - 1

            ! No wall has been hit yet
            ClosestDistance = huge(0.0_c_float)

            HitX = 0.0_c_float
            HitY = 0.0_c_float


            ! Ray direction
            RayDirX = cos(Angle(i))
            RayDirY = sin(Angle(i))


            ! Test this ray against every wall
            do j = 0, WallCount - 1

                ! Wall direction
                WallDirX = WallX2(j) - WallX1(j)
                WallDirY = WallY2(j) - WallY1(j)


                ! Denominator
                Denom = RayDirX * WallDirY - &
                        RayDirY * WallDirX


                ! Ignore parallel / nearly parallel walls
                if (abs(Denom) < 0.000001_c_float) then
                    cycle
                end if


                ! Difference between ray origin and wall
                DeltaX = WallX1(j) - RayX
                DeltaY = WallY1(j) - RayY


                ! Distance along ray
                T = (DeltaX * WallDirY - &
                     DeltaY * WallDirX) / Denom


                ! Position along wall
                U = (DeltaX * RayDirY - &
                     DeltaY * RayDirX) / Denom


                ! Valid intersection?
                if (T >= 0.0_c_float .and. &
                    U >= 0.0_c_float .and. &
                    U <= 1.0_c_float) then


                    ! Is this the closest wall so far?
                    if (T < ClosestDistance) then

                        ClosestDistance = T

                        HitX = RayX + T * RayDirX
                        HitY = RayY + T * RayDirY

                    end if

                end if

            end do


            ! Store the closest hit for this ray
            OutputX(i) = HitX
            OutputY(i) = HitY
            OutputDist(i) = ClosestDistance

        end do


    end subroutine GetRayData


end module Raycasting