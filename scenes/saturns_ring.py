#!/usr/bin/python3

import math

def generate_ring(center_x, center_y, center_z, radius, nb_spheres):
    sphere_list = []
    y = center_y
    coef = (center_y * 2) / (nb_spheres / 2)
    for i in range(nb_spheres):
        angle = 360 * i / nb_spheres
        x = center_x + radius * math.cos(math.radians(angle))
        if i <= nb_spheres / 2:
            y -= coef 
        else:
            y += coef
        z = center_z + radius * math.sin(math.radians(angle))
        sphere_list.append((x, y, z))
    return sphere_list

def main():
    saturn_center = (0, 3, 10)
    radius = 13
    nb_spheres = 200
    sphere_coordinates = generate_ring(saturn_center[0], saturn_center[1], saturn_center[2], radius, nb_spheres)
    for i, (x, y, z) in enumerate(sphere_coordinates):
        print(f"sp {x:.5f},{y:.5f},{z:.5f}               0.5                255,255,255\n")

if __name__ == '__main__':
    main()